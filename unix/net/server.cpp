#include<stdio.h>
#include<string.h>
#include<unistd.h>

#include<arpa/inet.h>
#include<sys/socket.h>

#define SIZE 128

int main(int argc, char ** argv)
{
  int sock = -1;
  
  //套接字的结构
  struct sockaddr_in addr;
  
  addr.sin_family=AF_INET;
  addr.sin_port = htons(9000);
  inet_pton(AF_INET,"192.168.3.38",&addr.sin_addr.s_addr);
  //addr.sin_addr.s_addr=[0|INADDR_ANY]通配，把主机的所有ip地址关联上
  //创建一个套接字的符号，标志类似文件的fd

  struct sockaddr_in cli_addr;
  
  sock=socket(AF_INET,SOCK_DGRAM,0);
  if(-1 == sock){
    perror("socket");
    return 1;
  }

  //绑定一个套接字
 int ret = bind(sock,(struct sockaddr* )&addr,sizeof(addr));
 if(-1 == ret){
   perror("bind");
   return 1;
 }
 char buf[SIZE]="";
 socklen_t len =sizeof(cli_addr);

 while(1){
   memset(buf,0,SIZE);
   //接受到信息
   recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr *)&cli_addr,&len);

   printf("%s\n",buf);

   //回复
   sendto(sock,buf,sizeof(buf),0,
	  (struct sockaddr *)&cli_addr,sizeof(cli_addr));
     
 }
 close(sock);
  
return 0;
}
