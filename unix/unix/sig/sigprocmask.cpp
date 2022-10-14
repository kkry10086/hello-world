#include<iostream>
#include<unistd.h>
#include<signal.h>

using std::cout;using std::endl;
using std::cin;

void fun(int signum){

  cout<<"捕捉到信号"<<signum<<endl;
}

//信号阻塞集
int main(int argc , char * argv[]){

  int ret=-1;
  //信号集
  sigset_t set;
  sigset_t old;

  //Ctrl+c
  signal(SIGINT,fun);

  //Ctrl+"\"
  signal(SIGQUIT,fun);

  cout<<"按下任意建阻塞信号"<<endl;
  getchar();

  sigemptyset(&old);

  sigemptyset(&set);
  sigaddset(&set,SIGINT);

  //设置屏蔽信号为2的信号
  
  ret=sigprocmask(SIG_BLOCK,&set,&old);

  if(-1==ret){
    perror("sigprocmask");
    return 1;
  }

  cout<<"设置屏蔽信号为2的信号成功..."<<endl;

  cout<<"按下任意建解除对信号2的屏蔽"<<endl;
  getchar();

  //将信号屏蔽集恢复为原来的集合
  ret=sigprocmask(SIG_SETMASK,&old,NULL);

  if(-1==ret){
    perror("sigprocmask");
    return 1;
  }

  cout<<"按下任意建退出"<<endl;
  getchar();
  
   
  
  return 0;
}
