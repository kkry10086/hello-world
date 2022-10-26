#include <stdio.h> 
 #include <string.h> 
#include<arpa/inet.h>
#include<sys/socket.h>
 
#define SIZE 128

int main(int argc, char ** argv)
{
   int sock = -1;
   //套接字结构体
   struct sockaddr_in addr;
   char buf[SIZE]="";
   //套接字结构体的创建
   addr.sin_family=AF_INET;
   addr.sin_port=htons(9000);
   inet_pton(AF_INET,argv[1],&addr.sin_addr.s_addr);
   
   //创建套接字的符号
   sock= socket(AF_INET,SOCK_DGRAM,0);
   if(-1 == sock){
       perror("socket");
       return 1;
   }


   //循环进行
   while(1){
       memset(buf,0,SIZE);
       fgets(buf,SIZE,stdin);
       sendto(sock,buf,strlen(buf),0,(struct sockaddr *)&addr,sizeof(addr));
       memset(buf,0,SIZE);
       recvfrom(sock,buf,SIZE,0,NULL,NULL);
       printf("receive: %s\n",buf);
   }

return 0; 
}




