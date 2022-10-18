#include<iostream>
#include<pthread.h>
#include<unistd.h>

using std::cout;using std::endl;

//线程的任务
void *fun(void *arg){
  int i=0;
  for(i=0;i<5;i++){
    cout<<"new pthread working"<<i<<endl;
    sleep(1);
  }
  cout<<"new thread exit"<<endl;
  return NULL;
}

int main(int argc, char ** argv){

  int ret=-1;
  pthread_t tid=-1;

  //创建一个线程
  ret=pthread_create(&tid,NULL,fun,NULL);
  if(0!=ret){
    cout<<"pthread_create failed"<<endl;
    return 1;
  }

  
  cout<<"main thread tid:"<<pthread_self()<<endl;

  //设置线程分离：
  ret=pthread_detach(tid);
  if(0!=ret){
    cout<<"pthread_detach failed"<<endl;
    return 1;
  }

  
  sleep(3);
  cout<<"main thread sleep 3s and cancel new thread"<<endl;

  pthread_cancel(tid);
						 
  cout<<"main thread exit"<<endl;
  return 0;
}
