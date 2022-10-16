#include<iostream>
#include<pthread.h>

using std::cout;using std::endl;


int num=100;

void *fun(void *arg){

  int *p=(int *)arg;
  
  cout<<"before: new thread.num:"<<num<<endl;
  cout<<"before: new thread.*p:"<<*p<<endl;
  num++;
  (*p)+=1;
  cout<<"after: new thread.num:"<<num<<endl;
  cout<<"after: new thread.*p:"<<*p<<endl;
  return NULL;
}
//验证数据共享
int main(int argc, char** argv){
  pthread_t tid=-1;
  int ret=-1;
  int *p;

  p=new int();
  if(NULL==p){
    cout<<"new int () failed"<<endl;
    return 1;
  }
  *p=123;
  
  //创建进程
  ret=pthread_create(&tid,NULL,fun,(void*)p);
  if(0!=ret){
    cout<<"pthread_create failed"<<endl;
    return 1;
  }

  cout<<"按下任意键继续"<<endl;
  getchar();
  cout<<"主线程：num="<<num<<endl;
  cout<<"主线程：p="<<*p<<endl;
  delete(p);
  return 0;
}
