#include<iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using std::string;
using std::cout;using std::endl;

int main(int argc, char ** argv)
{
	//判断有没有传输ip地址进来
	if(2 != argc){
		cout<<"using a.out ipaddress"<<endl;
		return 1;
	}


	int sock = -1;
	struct sockaddr_in addr;
	short port = 8000;

	//创建一个socket
	sock = socket(AF_INET,SOCK_DGRAM,0);

	if(-1 == sock){
		perror("socket");
		return 1;
	}

	//将addr 置空
	memset(&addr,0,sizeof(addr));

	//destination 的socket
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(argv[1]);

    
	//设置sock可以广播
	int yes = 1;
	int ret = setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&yes,sizeof(yes));

	if( 0 != ret){
		perror("setsockopt");
		return 1;
	}
    
	//发送的信息
	string msg = "testing broadcast !!!";

    int len = -1;
    len = sendto(sock,msg.data(),msg.length(),0,
	(struct sockaddr *)&addr,sizeof(addr));

	if( -1 == len){
		perror("sendto");
		return 1;
	}

	cout<<"发送的数据的长度:"<<len<<","<<"发送的数据:"<<msg<<endl;


     close(sock);


	return 0;
}
