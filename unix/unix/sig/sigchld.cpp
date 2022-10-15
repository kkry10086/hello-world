#include<iostream>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>

using std::cout;using std::endl;

void fun(int signum){
 
  pid_t pid;
  while((pid=waitpid(-1,NULL,WNOHANG))>0){
     cout<<"捕捉到信号："<<signum<<endl;
     cout<<"父进程得到子进程结束："<<pid<<endl;
  }
}

int main(int argc, char ** argv){


  pid_t pid =-1;

  struct sigaction act;
  act.sa_handler=fun;
  act.sa_flags=0;

  //注册信号处理函数
  sigaction(SIGCHLD, &act, NULL);
  
  
  //创建一个子进程
  pid=fork();

  if(-1==pid){
    perror("fork");
    return 1;
  }

  //子进程
  if(0==pid){
    cout<<"子进程睡眠两秒"<<endl;
    sleep(3);
    cout<<"子进程退出"<<endl;

    exit(0);
  }
  //父进程
  else{
    while(1){
      cout<<"父进程工作："<<endl;
      sleep(1);
    }
  }

  
  return 0;
}
