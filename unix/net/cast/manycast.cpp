#include<iostream>
#include<string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using std::cout;using std::endl;using std::cin;
using std::string;

int main(int argc, char ** argv)
{
   string group = "224.0.0.1";
   string local_ip = "172.28.128.26";

   //定义一个多播组地址
   struct ip_mreq mreq;
   int sock = socket(AF_INET,SOCK_DGRAM,0);
   struct sockaddr_in addr;

   addr.sin_family=AF_INET;
   addr.sin_port = 8000;
   addr.sin_addr.s_addr = inet_addr(group.data());

   //添加一个多播组ip
   mreq.imr_multiaddr.s_addr = inet_addr(group.c_str());
   mreq.imr_interface.s_addr = htonl(INADDR_ANY);

   setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));

   string msg = "can you see the msg using manycast?";
   sendto(sock,msg.c_str(),msg.length(),0,(struct sockaddr *)&addr,sizeof(addr));
   
   
   setsockopt(sock,IPPROTO_IP,IP_DROP_MEMBERSHIP,&mreq,sizeof(mreq));
   

   close(sock);

	return 0;
}
