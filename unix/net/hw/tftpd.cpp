#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "talk.h"

char *ip="172.28.136.107";
#define SIZE 128

//客户端的sockaddr_in
//不知为何在创建线程的时候会被memset 0
//自己太粗心了，下面有一个相同名字的局部变量
struct sockaddr_in cli_addr;

//信号量
//建好的cli_addr的资源，自线程就可以将cli_addr用来与客户端对话
sem_t read_addr;
//空的cli-addr的资源，线程就可以接受新的请求
sem_t write_addr;

void * pthread_talk(void *arg){

    printf("new thread\n");
    

    //读到资源，将空的资源减1，
    //buf与cli_addr必须写在sem_wait和sem_post之间，保证两个数据
    //都由同一线程获得
    sem_wait(&read_addr);

    
    //获得客户端发来的信息
    char *buf = (char *)arg;
    printf("from client: %s\n",buf);

    struct sockaddr_in cli;
    //拷贝到cli
    memcpy(&cli,&cli_addr,sizeof(cli_addr));
    //test whether get the cli_addr or no
    //10/27发现cli是空的,在新建pthread时候cli_addr就会便成为空的。
   
    char *temp = inet_ntoa(cli.sin_addr);
    printf("af:%d port:%d ip:%s \n",
           cli.sin_family,ntohs(cli.sin_port),temp);

    
    //将可以新写入的资源数量加一
    sem_post(&write_addr);

    //已经可以连接了，现在是对数据解析了
    server_talk(buf,&cli);
    
    pthread_exit(NULL);

}

//////////////////////////////////////////////

//实现tftpd
int main(int argc, char ** argv)
{
    int sock =-1;
    //服务器的sockaddr_in
    struct sockaddr_in server_addr;


    //cli_addr的大小
    socklen_t cli_len=sizeof(struct sockaddr_in);
    
    char buf[SIZE]="";

    //创建套接字符号
    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(-1 == sock){
        perror("socket");
        return 1;
    }

    //生成套接字的结构
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(9000);
    //给套接字增加ipaddress
    inet_pton(AF_INET,ip,&server_addr.sin_addr.s_addr);

    if(-1 == bind(sock,(struct sockaddr *)&server_addr,sizeof(server_addr)))
    {
        perror("bind");
        return 1;
    }

    //由于只能传一个数据，所以不能传cli_addr和buf
    //这里决定传buf，所以cli_addr作为全局变量
    //这里需要使用信号量来做到对cli_addr的访问控制
    //初始化信号量
    sem_init(&read_addr,0,1);
    sem_init(&write_addr,0,1);
   while(1){

       //将write的资源减1
       sem_wait(&write_addr);

       memset(buf,0,SIZE);
       memset(&cli_addr,0,sizeof(struct sockaddr_in));
       printf("cli_addr memset 0\n");

       recvfrom(sock,buf,SIZE,0,(struct sockaddr *)&cli_addr,&cli_len);
       
       
       //使用线程来实现对话,实现对话的函数在其他头文件里面
       pthread_t tid = -1;
       //新生成一个线程
       pthread_create(&tid,NULL,pthread_talk,(void *)buf);
       //将新线程的回收工作交由系统来执行
       pthread_detach(tid);

       //将read的资源加1
       sem_post(&read_addr);
       sleep(10);
   }

   //销毁信号量
   sem_destroy(&read_addr);
   sem_destroy(&write_addr);

   //关闭sock
   close(sock);
    return 0;
}
