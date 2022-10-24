#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

//信号量变量
sem_t sem;

///cout upper letters
void *fun1(void *arg){
	int i=0;

	//申请资源，将可用资源减一
	sem_wait(&sem);
	for(i = 'a';i <= 'z'; i++){
		putchar(i);
		fflush(stdout);
		usleep(100000);
	}

	//释放资源，将可用资源加一
	sem_post(&sem);

	pthread_exit(NULL);
}
//cout lower letters
void *fun2(void *arg){
	int i=0;

	//申请资源，将可用资源减一
	sem_wait(&sem);
	for(i = 'A'; i<= 'Z'; i++){
		putchar(i);
		fflush(stdout);
		usleep(100000);
	}

	//释放资源，将可用资源加一
	sem_post(&sem);

	pthread_exit(NULL);
}


int main(int argc,char ** argv){
	int ret=-1;
	pthread_t tid1,tid2;


	//初始化信号量
	ret = sem_init(&sem,0,1);
	if(0!= ret){
		printf("set_init failed\n");
		return 1;
	}
	printf("sem_init succeed\n");

	//生成两个线程
	pthread_create(&tid1,NULL,fun1,NULL);
	pthread_create(&tid2, NULL, fun2, NULL);



	//回收线程资源
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	//销毁信号量
	sem_destroy(&sem);

	return 0;
}
