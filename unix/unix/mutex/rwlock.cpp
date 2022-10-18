#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

using std::cout;using std::endl;

int num=0;
//读写锁变量
pthread_rwlock_t rwlock;

void * fun_read(void *arg){

  int index=(int)(long)arg;
  while(1){
    //加读写锁的读锁
    pthread_rwlock_rdlock(&rwlock);
    
    printf("线程%d 读取%d\n",index,num);

    //解锁
    pthread_rwlock_unlock(&rwlock);
    
    //随机睡眠1-3秒
    sleep(random()%3+1);
  }
  return NULL;
}

void * fun_write(void *arg){
  int index=(int)(long)arg;
  while(1){
    //增加读写锁的写锁
    pthread_rwlock_wrlock(&rwlock);
    
    num++;
    printf("线程%d 修改%d\n",index,num);
    
    //解锁
    pthread_rwlock_unlock(&rwlock);
    
    //随机睡眠1-3秒
    sleep(random()%3+1);
  }

  return NULL;
}

int main(){
  int ret=-1;
  pthread_t tid[8];

  int i=0;
  srandom(getpid());

  //初始化读写锁
  ret=pthread_rwlock_init(&rwlock,NULL);
  if(0!=ret){
    cout<<"pthread_rwlock_init failed"<<endl;
    return 1;
  }
  
  //创建8个线程
  for(i=0;i<8;i++){
    //创建读线程
    if(i<5){
      pthread_create(&tid[i],NULL,fun_read,(void *)(long)i);
    }
    //创建写线程
    else{
      pthread_create(&tid[i],NULL,fun_write,(void *)(long)i);
    }
  }

  for(i=0;i<8;i++){
    pthread_join(tid[i],NULL);
  }

  //销毁读写锁
  pthread_rwlock_destroy(&rwlock);


  return 0;
}
