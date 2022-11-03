#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<iostream>
#include<string.h>

using std::cout;using std::cin;
using std::endl;

int Accept(int fd,struct sockaddr *sa,socklen_t *salenptr){

	int n = -1 ;
again:
	if((n = accept(fd,sa,salenptr))<0){
		//ECONNABORTED是收到信号而出错，
		//EINTR是收到客户端发来的报文中falgs中由RST(ReSet)，
		//RST是用来断开链接用的
		if( (errno == ECONNABORTED) || (errno == EINTR)){
			goto again;
		}
		else{
			perror("accept error:");
			exit(1);
		}
	}
	return n;
}

int Bind(int fd,struct sockaddr * addr,socklen_t len){
	int ret = bind(fd,addr,len);
	if(-1 == ret){
		perror("bind");
		exit(1);
	}
	return ret;
}


int Tcp4_bind(short port,const char *ip){
	struct sockaddr_in ser_addr;
	int sock = socket(AF_INET,SOCK_STREAM,0);
	
	//将服务器套接字的结构体的信息写入
	memset(&ser_addr,0,sizeof(ser_addr));
	if( NULL == ip ){
		//如果ip为空，使用0.0.0.0，这个主机的任意ip将可以链接
		ser_addr.sin_addr.s_addr = INADDR_ANY;

	}else{
		int ret = inet_pton(AF_INET,ip,&ser_addr.sin_addr.s_addr);
		if(-1 == ret ){
			perror("inet_pton");
			exit(1);
		}else if(0 == ret){
			cout<<"ip is not a valid network address"<<endl;
			exit(1);
		}
	}

	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(port);

	//绑定结构体
	Bind(sock,(struct sockaddr *)&ser_addr,sizeof(ser_addr));

	//返回套接字
	return sock;



}
