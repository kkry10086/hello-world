#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

//创建无名管道
int main(){
  int fds[2];
  int ret=-1;

  ret=pipe(fds);
  if(-1==ret){

    perror("pipe");
    return 1;
  }
  printf("fd[0]:%d ,fd[1]:%d\n",fds[0],fds[1]);

  close(fds[0]);
  close(fds[1]);
  return 0;
}
