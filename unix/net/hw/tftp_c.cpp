#include<stdio.h>
#include<string.h>

#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#include "download.h"

char *ip="172.28.136.107";
#define SIZE 512

int main(int argc, char ** argv)
{
    // if(2 != argc){
    //     printf("using a.out ip_addr");
    //     return 1;
    // }
    int sock = -1;
    //目标结构体
    struct sockaddr_in addr;
  
    
    //生成一个套接字描述符
    sock= socket(AF_INET,SOCK_DGRAM,0);

    //目标的socket
    addr.sin_family=AF_INET;
    addr.sin_port= htons(9000);
    inet_pton(AF_INET,ip,&addr.sin_addr.s_addr);

   
    //请求下载的文件名
    char filename[128]="/home/kali/unix/net/hw/download.cpp";
    
    
    //实现下载的功能
    //请求下载的数据的格式
    char buf[SIZE];
    sprintf(buf,"%c%c%s%c%s%c",'0','1',filename,'\0',"octet",'\0');
    
    sendto(sock,buf,sizeof(buf),0,(struct sockaddr *)&addr,sizeof(addr));
    printf("sendto --%s-- recvfrom\n",buf);
    receiveD(sock);
   
    
    //关闭sock
    close(sock);

    return 0;
}
