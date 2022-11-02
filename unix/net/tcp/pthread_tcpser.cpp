#include<iostream>
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

using std::cout;using std::endl;using std::cin;
using std::string;

typedef class sock_sockaddr{
	private:
		int sock;
		struct sockaddr_in addr;

     public:
		sock_sockaddr(int asock,struct sockaddr_in aaddr){
			sock = asock;
			addr = aaddr;
		}
		int get_sock(){
			return sock;
		}
		struct sockaddr_in get_sockaddr_in(){
			return addr;
		}
		~sock_sockaddr(){
			close(sock);
		}

} SS;


#define SIZE 1024

void *talk_client(void * arg){
	SS *info = (SS *)arg;

	cout<<"client ip:"<<inet_ntoa(info->get_sockaddr_in().sin_addr) 
		<<", port:"<< ntohs(info->get_sockaddr_in().sin_port)<<endl;

	while(1){
		char buf[SIZE]="";
		int n = read(info->get_sock(),buf,SIZE);
		if( 0 == n ){
			cout<<"connection closed"<<endl;
			break;
		}
		cout<<"recv:"<<buf<<endl;

		write(info->get_sock(),buf,strlen(buf));

	}
	//回收堆中的SS资源还有关闭相应的socket
	//全放在了类中的析构函数实现

	delete(info);
	pthread_exit(0);

}
int main(int argc, char ** argv)
{
	int s_sock = -1;
	string ip = "192.168.3.38";
	//已连接，未连接两条队列的最大之和
	int backlog = 128;

	//创建套接字
	s_sock = socket(AF_INET,SOCK_STREAM,0);
	if( -1 == s_sock ){
		perror("socket");
		return 1;
	}

	//要绑定的IP与port的结构体
	struct sockaddr_in s_addr;
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(9000);
	inet_pton(AF_INET,ip.data(),&s_addr.sin_addr.s_addr);

    //设置端口复用
    int opt = -1;
    setsockopt(s_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	//绑定套接字与结构体中的信息
	bind(s_sock,(struct sockaddr *)&s_addr,sizeof(s_addr));

	//监听套接字
	listen(s_sock,backlog);

	while(1){
		struct sockaddr_in c_addr;
		socklen_t len = sizeof(c_addr);
		int c_sock = accept(s_sock,(struct sockaddr *)&c_addr,&len);

		//发送给其他线程使用的数据
		SS *msg = new SS(c_sock,c_addr);

		pthread_t tid = -1;

		pthread_create(&tid,NULL,talk_client,(void *)msg);
		pthread_detach(tid);
	}



	return 0;
}
