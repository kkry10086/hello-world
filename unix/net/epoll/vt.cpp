#include<iostream>
#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include"wrap.h"

using std::cout;using std::endl;using std::cin;
using std::string;

#define backlog 128
#define SIZE 1024

int main(int argc, char ** argv)
{

	//epoll_wait返回的数组
	struct epoll_event evs[SIZE];
	//创建套接字
	//绑定套接字
	int lfd = Tcp4_bind(9000,NULL);

	//监听
	listen(lfd,backlog);

	//创建epoll树
	int epfd = epoll_create(1);

	//将lfd上树
	struct epoll_event levent;
	levent.events = EPOLLIN;//监听读事件
	levent.data.fd = lfd;
	epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&levent);

	//循环监听树
	while(1){
		int n = epoll_wait(epfd,evs,SIZE,-1);
		if(n < 0){
			perror("epoll_wait ");
			exit(1);
		}
		else if(0 == n){
			continue;
		}
		else{
			for(int i =0;i<n;i++){

				int fd = evs[i].data.fd;
				//如果是lfd变化并且是读事件变化
				if(fd == lfd && evs[i].events & EPOLLIN){
					struct sockaddr_in cli;
					socklen_t len = sizeof(cli);
					int sock = Accept(lfd,(struct sockaddr *)&cli,&len);
					cout<<"client ip:"<<inet_ntoa(cli.sin_addr)
						<<"client port:"<<ntohs(cli.sin_port)<<endl;

					//sock设为非阻塞,read就会一直读下去，不会阻塞
					int flag = fcntl(sock,F_GETFL);
					flag |= O_NONBLOCK;
					fcntl(sock,F_SETFL,flag);

					//将sock加入epoll树，同时加上边沿触发
					levent.events = EPOLLIN | EPOLLET;
					levent.data.fd = sock;
					epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&levent);


				}
				//除了lfd变化并且是读事件变化
				else if(evs[i].events & EPOLLIN){
					while(1){
						char buf[5]="";
						int ret = read(evs[i].data.fd,buf,sizeof(5));
						if(-1 == ret){
							if(errno == EAGAIN){
								//代表缓冲区没有数据
								break;
							}
							else{
								perror("read");
								close(evs[i].data.fd);
								epoll_ctl(epfd,EPOLL_CTL_DEL,
										evs[i].data.fd,&evs[i]);
								break;
							}
						}
						if( ret == 0){
							//断开连接
							cout<<"connection close"<<endl;
							close(evs[i].data.fd);
							epoll_ctl(epfd,EPOLL_CTL_DEL,
									evs[i].data.fd,&evs[i]);
							break;
						}
						else{
							cout<<buf<<endl;
							write(evs[i].data.fd,buf,strlen(buf));
						}
					}

				}

			}
		}
	}

	//关闭树

	return 0;
}
