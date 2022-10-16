#include<iostream>
#include<pthread.h>
#include<unistd.h>

using std::cout;using std::endl;

void *fun(void *arg){
  for(int i=0;i<3;i++){
    cout<<"new pthread is running"<<endl;
    sleep(1);
  }
  return (void *)0x3;
}


//回收线程资源
int main(int argc,char** argv){

  pthread_t tid=-1;
  int ret=-1;
  void *retval=NULL;
 
  ret=pthread_create(&tid,NULL,fun,NULL);
  if(0!=ret){
    cout<<"pthread_create failed"<<endl;
    return 1;
  }

  cout<<"main pthread is running "<<endl;
    
  ret=pthread_join(tid,&retval);
  if(0!=ret){
    cout<<"pthread_join failed"<<endl;
    return 1;
  }
  cout<<"retval:"<<retval<<endl;
  cout<<"主线程退出"<<endl;
  
  return 0;
}
