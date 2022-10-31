#include<iostream>
#include<string>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

using std::cout;using std::endl;using std::cin;
using std::string;

#define SIZE 256

int main(int argc, char ** argv)
{
	//目的IP
	string ip = "192.168.3.38";


	//1.创建流式套接字
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == sock){
		perror("socket");
		return 1;
	}

    //2.创建连接的服务器的结构体
	struct sockaddr_in ser_addr;
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(9000);
	//这里要的数据是指针，所以不能使用string::c_str()
	ser_addr.sin_addr.s_addr = inet_addr(ip.data());

    socklen_t ser_addr_len = sizeof(ser_addr);

	cout<<"connect:"<<endl;

	//3.链接服务器
    int ret = connect(sock,(struct sockaddr *)&ser_addr,ser_addr_len);
	if(-1 == ret){
	perror("connect");
	return 1;
	}


	//4.收发数据
	while(1){
		//发送的数据
		string smsg;
		//接收数据的char 数组；
		//因为string的data()是cosnt char *，无法修改
		char rmsg[SIZE];
		
		cout<<"what send to server ?"<<endl;
		cin>>smsg;
		write(sock,smsg.data(),smsg.length());
		int len = read(sock,rmsg,SIZE);
		if(0 == len){
			cout<<"connection close"<<endl;
			break;
		}

		cout<<"recving msg:"<<rmsg<<endl;

	}


	//4.关闭套接字
	close(sock);


	return 0;
}
