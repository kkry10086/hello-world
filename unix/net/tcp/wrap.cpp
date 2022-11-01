#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>

int Accept(int fd,struct sockaddr *sa,socklen_t *salenptr){

	int n = -1 ;
again:
	if((n = accept(fd,sa,salenptr))<0){
		//EINTR是收到信号而出错，
		//ECONNABORTED是收到客户端发来的报文中falgs中由RST(ReSet)，
		//RST是用来断开链接用的
		if( (errno == ECONNABORTED) || (errno == EINTR)){
			goto again;
		}
		else{
			perror("accept error:");
			exit(1);
		}
	}
}
