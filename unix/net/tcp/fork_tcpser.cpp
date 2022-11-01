#include<iostream>
#include<string>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

using std::cout;using std::endl;using std::cin;
using std::string;

#define SIZE 512

//SIGCHLD处理函数
void fun(int signum,siginfo_t *info,void *context){
	int wstatus;
		while(waitpid(-1,&wstatus,WNOHANG) > 0){
		if(WIFEXITED(wstatus)){
			cout<<"normal.子进程退出码：" << WEXITSTATUS(wstatus) <<endl;
		
		}
		else{
			cout<<"子进程退出码：" << WEXITSTATUS(wstatus) <<endl;

		}

	}
	
}

//由于收到SIGCHID,accept会收到影响，例如：
//会执行，然后，然后就是返回-1，然后后面就会继续运行
//此时由于没有生成c_sock，所以子进程结束，然后父进程就会返回结果
//但是这样不会导致连续的反应，这时子进程的sigchld，不会对accept产生影响
int main(int argc, char ** argv)
{


	//实现对子进程的信号的捕捉与其资源的回收
	struct sigaction act;
	/*act.sa_flags = 0;
	  act.sa_handler = fun;
	 */
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = fun;
	//将临时的阻塞集置空
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD,&act,NULL);
	
	/* 用不到
	   将sigchld加入到阻塞集
	
	   sigset_t set;
	   sigemptyset(&set);
	   sigaddset(&set,SIGCHLD);
	   sigprocmask(SIG_BLOCK,&set,NULL);
	 */
	int s_sock = -1;
	//监听ip与地址的结构体
	struct sockaddr_in s_addr;


	//两个队列的数量的和的最大值,一般是128
	int backlog = 128;
	//ip地址
	string ip ="192.168.50.2";


	//1.创建套接字,监听的ip与port等信息的结构体
	s_sock = socket(AF_INET,SOCK_STREAM,0);
	s_addr.sin_family =AF_INET;
	s_addr.sin_port  = htons(9000);
	inet_pton(AF_INET,ip.data(),&s_addr.sin_addr.s_addr);



	//2.绑定套接字
	bind(s_sock,(struct sockaddr *)&s_addr,sizeof(s_addr));


	//3.监听套接字，创建两个链接队列，
	//已完成链接队列；未完成链接队列
	listen(s_sock,128);


	pid_t pid =1;


	//5.循环接收链接请求(accept),
	//从已完成链接队列提取新的链接，创建一个新的链接套接字，
	//使用这个已连接套接字和当前这个客户端通信

	while(1){

		//客户端的信息的结构体
		struct sockaddr_in c_addr;
		socklen_t c_addr_len;
		int c_sock = accept(s_sock,(struct sockaddr *)&c_addr,&c_addr_len);

		if( -1 == c_sock){
			cout<<"进程ip"<<getpid()<<endl;
			perror("accept");
			cout<<"client ip :"<<inet_ntoa(c_addr.sin_addr)
				<<"client port"<<ntohs(c_addr.sin_port)<<endl;
			continue;
		}

		//5. 创建子进程
		pid = fork();

		//父进程
		if(pid >0 ){
			cout<<"父进程的pid:"<<getpid()<<endl;
			close(c_sock);
			//实现对子进程的信号的捕捉与其资源的回收
			struct sigaction act;
			/*act.sa_flags = 0;
			  act.sa_handler = fun;
			 */
			act.sa_flags = SA_SIGINFO;
			act.sa_sigaction = fun;
			//将临时的阻塞集置空
			sigemptyset(&act.sa_mask);
			sigaction(SIGCHLD,&act,NULL);
			//把整个进程的信号集中去掉SIGCHLD
			//sigprocmask(SIG_UNBLOCK,&set,NULL);

		}
		else if(0 == pid){
			cout<<"子进程的pid:"<<getpid()<<endl;
			close(s_sock);

			char msg[SIZE];
			int ret = -1;
			//收发信息
			while(1){
				memset(msg,0,SIZE);

				//读取数据
				ret = read(c_sock,msg,SIZE);
				if(-1 == ret){
					perror("read");
					exit(0);
				}
				if( 0 == ret ){	
					cout<<"connection close"<<endl;
					exit(0);
				}
				cout<<"read:"<<msg<<endl;

				//发送数据
				write(c_sock,msg,strlen(msg));

			}
			cout<<"out while"<<endl;
			//关闭套接字i
			exit(0);
		}


	}
	//关闭套接字
	if(pid > 0){
		close(s_sock);
	}

	return 0;
}
