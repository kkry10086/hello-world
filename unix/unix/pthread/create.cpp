#include<iostream>
#include<pthread.h>

using std::cout;using std::endl;

void * fun1(void *arg){
  cout<<"新的线程的tid："<<pthread_self()<<endl;
  return NULL;
}

void * fun2(void *arg){
  int temp=(int)(long)arg;
  cout<<"第二个线程tid："<<pthread_self()<<endl;
  cout<<"参数是:"<<temp<<endl;
  return NULL;
  
}

int main(int argc,char** argv){

  pthread_t tid1=-1;
  pthread_t tid2=-1;
  int ret=-1;

  ret=pthread_create(&tid1,NULL,fun1,NULL);
  if(0!=ret){
    cout<<"创建线程失败"<<endl;
    return 1;
  }
  char to[]="123465";

  ret=pthread_create(&tid2,NULL,fun2,(void*)0x3);
  if(0!=ret){
    cout<<"创建线程失败"<<endl;
    return 1;
  }
  cout<<"主线程的tid："<<pthread_self()<<endl;

  cout<<"按下任意键退出"<<endl;
  getchar();
  
  return 0;
}
