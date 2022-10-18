#include<iostream>
#include<pthread.h>
#include<unistd.h>

using std::cout;using std::endl;

void *fun1(void* arg){
  int i=0;
  for(i='A';i<'Z';i++){
    putchar(i);
    fflush(stdout);
    usleep(100000);//100毫秒
  }
  return NULL;
}

void *fun2(void* arg){
  int i=0;
  for(i='a';i<'z';i++){
    putchar(i);
    fflush(stdout);
    usleep(100000);//100毫秒
  }
  return NULL;
}

//模拟输出字符
int main(int argc, char **argv){

  pthread_t tid1,tid2;

  //创建两个线程
  pthread_create(&tid1,NULL,fun1,NULL);
  pthread_create(&tid2,NULL,fun2,NULL);

  //等待线程结束
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);

  cout<<endl<<"主线程退出"<<endl;
  
  return 0;
}
