#include<iostream>
#include<string>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

using std::cout;using std::endl;using std::cin;
using std::string;

#define SIZE 512

int main(int argc, char ** argv)
{

	int s_sock = -1;
	//监听ip与地址的结构体
	struct sockaddr_in s_addr;

	//客户端的信息的结构体
	struct sockaddr_in c_addr;


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

	//4.接收链接请求(accept),
	//从已完成链接队列提取新的链接，创建一个新的链接套接字，
	//使用这个已连接套接字和当前这个客户端通信
	socklen_t c_addr_len;
	int c_sock = accept(s_sock,(struct sockaddr *)&c_addr,&c_addr_len);

	if( -1 == c_sock){
		perror("accept");
		cout<<"client ip :"<<inet_ntoa(c_addr.sin_addr)
			<<"client port"<<ntohs(c_addr.sin_port)<<endl;
	}

	char msg[SIZE];
	int ret = -1;
	//5.收发信息
	while(1){
		memset(msg,0,SIZE);

		//读取数据
		ret = read(c_sock,msg,SIZE);
		if( 0 == ret ){
			perror("read");
			close(c_sock);
			close(s_sock);
			return 1;
		}
		cout<<"read:"<<msg<<endl;


		//发送数据
		write(c_sock,msg,strlen(msg));

	}


	//6.关闭套接字
	close(c_sock);
	close(s_sock);


	return 0;
}
