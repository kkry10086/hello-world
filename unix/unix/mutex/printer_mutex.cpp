#include<iostream>
#include<pthread.h>
#include<unistd.h>

using std::cout;using std::endl;

void *fun1(void* arg){
  pthread_mutex_t * temp=(pthread_mutex_t *)arg;
  int i=0;
  //加锁
  pthread_mutex_lock(temp);
  for(i='A';i<'Z';i++){
    putchar(i);
    fflush(stdout);
    usleep(100000);//100毫秒
  }
  cout<<endl;
  //解锁
  pthread_mutex_unlock(temp);
  return NULL;
}

void *fun2(void* arg){
  pthread_mutex_t * temp=(pthread_mutex_t *)arg;
  int i=0;
  //加锁
  pthread_mutex_lock(temp);
  for(i='a';i<'z';i++){
    putchar(i);
    fflush(stdout);
    usleep(100000);//100毫秒
  }
  cout<<endl;
  //解锁
  pthread_mutex_unlock(temp);
  return NULL;
}

//模拟输出字符
int main(int argc, char **argv){

  int ret=-1;
  pthread_t tid1,tid2;
  pthread_mutex_t mutex;

  //初始化一个互斥锁
  ret=pthread_mutex_init(&mutex,NULL);
  if(0!=ret){
    cout<<"初始化互斥锁失败"<<endl;
    return 1;
  }

  cout<<"初始化互斥量成功"<<endl;
  
  //创建两个线程
  pthread_create(&tid1,NULL,fun1,(void*)&mutex);
  pthread_create(&tid2,NULL,fun2,(void*)&mutex);

  //等待线程结束
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);

  //销毁互斥锁
  pthread_mutex_destroy(&mutex);
  cout<<endl<<"主线程退出"<<endl;
  
  return 0;
}
