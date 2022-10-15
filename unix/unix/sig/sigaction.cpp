#include<iostream>
#include<signal.h>
#include<unistd.h>

using std:: cout;using std::endl;
//信号处理函数
void fun(int signum)
{

  cout<<"捕捉到信号："<<signum<<endl;
}

//新的信号处理函数
void fun1(int signum, siginfo_t *info, void *context){
  cout<<"捕捉到信号:"<<signum<<endl;
}

//sigaction的使用
int main(int argc, char** argv){

  int ret=-1;



#if 0
    struct sigaction act;
  //使用旧的信号处理函数指针
  act.sa_handler=fun;

  //标志为默认，默认使用旧的信号处理函数指针
  act.sa_flags=0;
  
#else
  struct sigaction act;
  //使用新的信号处理函数指针
  act.sa_sigaction=fun1;

  //标志指定新的信号处理函数指针
  act.sa_flags=SA_SIGINFO;

  

#endif
  //信号处理函数的注册
  ret=sigaction(SIGINT,&act,NULL);

  if(-1==ret){
    perror("sigaction");
    return 1;
  }

  cout<<"按下任意建继续"<<endl;
  getchar();
  getchar();

	    
  return 0;
}
