#include<iostream>
#include<pthread.h>
#include<unistd.h>

using std::cout;using std::endl;

//编译时要指定链接线程库 -pthread
int main(int argc,char** argv){

  pthread_t tid=0;

  //获取当前线程号：
  tid=pthread_self();

  cout<<"tid:"<<tid<<endl;
  
  return 0;
}
