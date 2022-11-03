#include<iostream>
#include<string>

#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#include "wrap.h"

using std::cout;using std::endl;using std::cin;
using std::string;

//tcp的链接队列
#define backlog 128
#define SIZE 1024

int main(int argc, char ** argv)
{
	//创建套接字

	//绑定
	int lfd = Tcp4_bind(9000,NULL);

	//监听
	listen(lfd,backlog);

	//最大的文件描述符
	int max_fd = lfd;

	//两个文件描述符集合
	fd_set old_fset,r_fset;
	//清空两个集合
	FD_ZERO(&old_fset);
	FD_ZERO(&r_fset);

	//把lfd加入old_fset，复制给r_fset;
	FD_SET(lfd,&old_fset);

	//属性变化的文件描述符的数量
	int nready = -1;

	//超时时间
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec =0;

	while(1){
		r_fset = old_fset;
		//使用select监听r_fset中每个文件描述符的读的缓冲区变化
		//r_fset会返回有变化的文件描述符
		nready = select(max_fd+1,&r_fset,NULL,NULL,NULL);
		if(0 == nready)
			continue;

		if(nready > 0){

			//有两种文件描述符，一种是监听的，一种是会话的

			//先看看监听的，lfd是否在r_fset里面
			if(FD_ISSET(lfd,&r_fset)){
				struct sockaddr_in cli;
				socklen_t cli_len ;
				int talk_sock =Accept(lfd,(struct sockaddr *)&cli,&cli_len);
				cout<<"client ip:"<<inet_ntoa(cli.sin_addr)
					<<"client port"<<ntohs(cli.sin_port)<<endl;
				//将talk_sock加入old_fset
				FD_SET(talk_sock,&old_fset);
				//假设max_fd小于talk_sock，改变max_fd
				//这样才能够探查到到新生成的fd的变化
				if(max_fd < talk_sock){
					max_fd = talk_sock;
				}

				//nready减一，并判断nready是否取完

				if(--nready <= 0){
					continue;
				}

			}
			for(int i = lfd+1;i <= max_fd;i++){
				//判断是否在r_fset里面
				if(FD_ISSET(i,&r_fset)){
					//进行交流
					char buf[SIZE];
					memset(buf,0,SIZE);
					int ret = read(i,buf,SIZE);
					if(-1 ==ret ){
						perror("read");
						close(i);
						FD_CLR(i,&old_fset);
						continue;
					}
					else if( 0 == ret){
						//ret == 0 表示断开链接
						FD_CLR(i,&old_fset);
						close(i);
						continue;
					}
					else{

						cout<<buf<<endl;

						write(i,buf,strlen(buf));
					}
				}

			}


		}

	}

	return 0;
}
