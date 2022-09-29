#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<unistd.h>

int main(){
  int fds[2];

  int ret=-1;

  ret=pipe(fds);
  if(-1==ret){
    perror("pipe");
    exit(1);
  }

  //fds[0]读,fds[1]写
  printf("fds[0]=%d ,fds[1]=%d\n",fds[0],fds[1]);

  printf("pipe size: %ld\n",fpathconf(fds[0],_PC_PIPE_BUF));
  printf("pipe size: %ld\n",fpathconf(fds[1],_PC_PIPE_BUF));
  

  close(fds[0]);
  close(fds[1]);
  return 0;
}
