#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

#define SIZE 64

int main(){
  int ret=-1;
  pid_t pid=-1;
  int fds[2]={3,4};

  char buf[SIZE];
  
  //创建无名管道
  ret=pipe(fds);
  if(-1==ret){
    perror("pipe");
    return 1;
  }

  //创建子进程
  pid=fork();
  if(-1==pid){
    perror("fork");
    return 1;
  }

  if(0==pid){
    //子进程
    close(fds[1]);
    
    printf("子进程读管道\n");

    //将子进程设为非阻塞
    ret=fcntl(fds[0],F_GETFL);
    ret |= O_NONBLOCK;
    fcntl(fds[0],F_SETFL,ret);
    ret=-1;

    
    ret=read(fds[0],buf,SIZE);
    if(0==ret){
      perror("read");
      exit(-1);
    }

    printf("子进程 读端：%s\n",buf);
    close(fds[0]);
    exit(0);
    
  }
  
    sleep(1);
    close(fds[0]);

    ret=write(fds[1],"abcdefghijklmnopqrstuvwxyz",26);
    if(0>ret){
      perror("write");
      exit(-1);
    }
    printf("parent write len:%d\n",ret);
    close(fds[1]);
    return 0;
  
  }
