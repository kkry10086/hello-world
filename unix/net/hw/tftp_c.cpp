#include<stdio.h>
#include<string.h>

#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define SIZE 516



int main(int argc, char ** argv)
{
    if(2 != argc){
        printf("using a.out ip_addr");
        return 1;
    }
    int sock = -1;
    //目标结构体
    struct sockaddr_in addr;
    //交互结构体
    struct sockaddr_in talk_addr;
    
    //生成一个套接字描述符
    sock= socket(AF_INET,SOCK_DGRAM,0);

    //目标的socket
    addr.sin_family=AF_INET;
    addr.sin_port= htons(9000);
    inet_pton(AF_INET,argv[1],&addr.sin_addr.s_addr);

    //发送数据
    char buf[SIZE] ="";
    //接受数据
    char rbuf[SIZE] ="";
    memset(buf,0,SIZE);
    memset(rbuf,0,SIZE);
    
    char filename[128]="~/git";
    socklen_t addrlen=sizeof(talk_addr);
    
    //实现下载的功能
    //请求下载的数据的格式
    sprintf(buf,"%c%c%s%c%s%c",'0','1',filename,0,"octet",0);
    
    sendto(sock,buf,strlen(buf),0,(struct sockaddr *)&addr,sizeof(addr));
    printf("sendto --%s-- recvfrom\n",buf);
    recvfrom(sock,rbuf,SIZE,0,(struct sockaddr *)&talk_addr,&addrlen);

    //判断操作码
    
    if( '0' == buf[0] && '3' == buf[1]){
        printf("s返回码是%s",rbuf);
    }
    else{
         printf("f返回码是%s",rbuf);
    }

    /*
    while(1){
        
    }
    
    */
    
    //关闭sock
    close(sock);

return 0;
}
