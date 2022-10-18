#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>

using std::cout;using std::endl;

void *fun(void *arg){
  for(int i=0;i<5;i++){
    cout<<"new thread is running "<<i<<endl;
  }
  return NULL;
}

int main(){
  int ret=-1;
  pthread_t tid=-1;
  pthread_attr_t attr;

  //初始化atrr
  ret=pthread_attr_init(&attr);
  if(0!=ret){
    cout<<"pthread_attr_init failed"<<endl;
    return 1;
  }

  

  //设置线程为分离状态
  ret=pthread_attr_setdetachstate
    (&attr,PTHREAD_CREATE_DETACHED);
  if(0!=ret){
    cout<<"setdetachstate failed"<<endl;
    return 1;
  }

  //创建线程
  ret=pthread_create(&tid,&attr,fun,NULL);
  if(0!=ret){
    cout<<"pthread_create failed"<<endl;
    return 1;
  }
    //测试是否为detach属性
  ret=pthread_join(tid,NULL);
  if(0!=ret){
    cout<<"pthread is detach"<<endl;
    return 1;
  }
  else{
    cout<<"pthread is not detach"<<endl;
  }

  cout<<"按下任意键退出"<<endl;
  getchar();
  
  //销毁线程属性
  ret=pthread_attr_destroy(&attr);
  if(0!=ret){
    cout<<"pthread_attr_destory failed"<<endl;
    return 1;
  }

 

  return 0;
}
