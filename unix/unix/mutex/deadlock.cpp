#include<iostream>
#include<pthread.h>
#include<unistd.h>

using std::cout;using std::endl;
pthread_mutex_t mutex1,mutex2;
//演示死锁
void *fun1(void* arg){
  //线程1先申请资源1再申请资源2
  pthread_mutex_lock(&mutex1);
  sleep(1);
  pthread_mutex_lock(&mutex2);
  cout<<"线程1执行临界区代码"<<endl;
  //解锁
  pthread_mutex_unlock(&mutex1);
  pthread_mutex_unlock(&mutex2);
  return NULL;
}

void *fun2(void* arg){
  //线程2先申请资源2再申请资源1
  pthread_mutex_lock(&mutex2);
  sleep(1);
  pthread_mutex_lock(&mutex1);
  cout<<"线程2执行临界区代码"<<endl;
  //解锁
  pthread_mutex_unlock(&mutex1);
  pthread_mutex_unlock(&mutex2);

  return NULL;
}

//模拟输出字符
int main(int argc, char **argv){

  int ret=-1;
  pthread_t tid1,tid2;
  pthread_mutex_t mutex;

  //初始化一个互斥锁
  ret=pthread_mutex_init(&mutex1,NULL);
  if(0!=ret){
    cout<<"初始化互斥锁失败"<<endl;
    return 1;
  }
   ret=pthread_mutex_init(&mutex2,NULL);
  if(0!=ret){
    cout<<"初始化互斥锁失败"<<endl;
    return 1;
  }

  cout<<"初始化互斥量成功"<<endl;
  
  //创建两个线程
  pthread_create(&tid1,NULL,fun1,NULL);
  pthread_create(&tid2,NULL,fun2,NULL);

  //等待线程结束
  ret=pthread_join(tid1,NULL);
  if(0!=ret){
    cout<<"pthread_join tid1 failed"<<endl;
    return 1;
  }
  ret=pthread_join(tid2,NULL);
  if(0!=ret){
    cout<<"pthread_join tid2 failed"<<endl;
    return 1;
  }

  //销毁互斥锁
  pthread_mutex_destroy(&mutex1);
  pthread_mutex_destroy(&mutex2);
  cout<<endl<<"主线程退出"<<endl;
  
  return 0;
}
