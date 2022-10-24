#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#include<pthread.h>
#include<unistd.h>

int flag= 0;

//条件变量
pthread_cond_t cond;
//互斥锁
pthread_mutex_t mutex;

// 改变条件的线程
void *fun1(void *arg){
//	printf("thread 1 go\n");

	while(1){
		//加锁
		pthread_mutex_lock(&mutex);
		flag = 1;

		//解锁
		pthread_mutex_unlock(&mutex);

		//唤醒因为条件而阻塞的线程

		pthread_cond_signal(&cond);

		sleep(2);
	}

	return NULL;
}

//等待条件的线程
void *fun2(void *arg){
//	printf("thread 2 go\n");

	while(1){

		//加锁
		pthread_mutex_lock(&mutex);

		if(0 == flag){
			//等待条件满足,会阻塞
			pthread_cond_wait(&cond,&mutex);
		}
		printf("线程2条件满足，继续运行\n");
		flag = 0;

		//解锁
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}



//条件变量的应用
int main(int argc,char ** argv){
	int ret=-1;
	pthread_t tid1,tid2;

	//初始化条件变量
	ret=pthread_cond_init(&cond,NULL);
	if(0!=ret){
		printf("pthread_cond_init faled...\n");
		return 1;
	}
	//初始化互斥锁
	ret=pthread_mutex_init(&mutex,NULL);
	if(0!=ret){
		printf("pthread_mutex_init faled...\n");
		return 1;
	}
	//初始化互斥锁


	//创建两个线程
	pthread_create(&tid1,NULL,fun1,NULL);
	pthread_create(&tid2,NULL,fun2,NULL);

	//回收线程资源
	ret=pthread_join(tid1,NULL);
	if(0!=ret){
		printf("pthread_join tid1 failed\n");
		return 1;
	}
	ret=pthread_join(tid2,NULL);
	if(0!=ret){
		printf("pthread_join tid2 failed\n");
		return 1;
	}

	//销毁互斥锁
	pthread_mutex_destroy(&mutex);
	//销毁条件变量
	pthread_cond_destroy(&cond);

	return 0;
}
