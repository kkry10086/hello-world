#include<iostream>
#include<unistd.h>

using std::cout;using std::endl;

//测试setsid和getsid
int main(int argc, char **argv){

  pid_t pid=-1;

  //获取当前进程组的pid
  pid=getsid(0);
  if(-1==pid){
    perror("getsid");
    return 1;
  }
  cout<<"sid: "<<pid<<endl;

  getchar();
  //新建一个会话
  pid=setsid();
  if(-1==pid){
    perror("setsid");
    return 1;
  }

  cout<<"新的会话"<<endl;
  
  return 0;
}
