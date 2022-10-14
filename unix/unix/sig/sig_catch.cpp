 #include<iostream>
#include<stdlib.h>
#include<signal.h>


using std::cout;using std::endl;

//信号处理函数
void fun1(int signum){
  cout<<"捕捉到信号"<<signum<<endl;
}
void fun2(int signum){
  cout<<"捕捉到信号"<<signum<<endl;
}
//信号注册函数
int main(){

  //Ctrl+c
  signal(SIGINT,fun1);

  //Ctrl+'\'
  signal(SIGQUIT,fun2);

  while(1){
    getchar();
    sleep(1);
  }
  
  return 0;
  
}
