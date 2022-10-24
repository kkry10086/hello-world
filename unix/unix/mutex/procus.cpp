#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<pthread.h>

//条件变量
pthread_cond_t cond;
//互斥量
pthread_mutex_t mutex;


typedef struct _node_t{
	int data;
	struct _node_t *next;
}node_t;

node_t *head=NULL;

//thread of producer
void *producer(void *arg){
	printf("producer\n");
	while(1){
		//加锁
		pthread_mutex_lock(&mutex);

		//分配节点空间
		node_t *ne =(node_t *) malloc(sizeof(node_t));

		if(NULL == ne){
			printf("malloc failed\n");
			break;
		}
		memset(ne , 0 , sizeof(node_t));

		ne->data = random()%100+1;
		ne->next = NULL;

		//头插法
		ne->next=head;
		head = ne;
		//解锁
		pthread_mutex_unlock(&mutex);

		printf("producer produce %d \n",ne->data);
		//唤醒因为条件变量而阻塞的线程
		pthread_cond_signal(&cond);

		sleep(random()%3+1);
	}
	pthread_exit(NULL);
}

//thread of customer
void *customer(void *arg){
	printf("customer\n");
    //加锁
	pthread_mutex_lock(&mutex);

	node_t *temp=NULL;
	while(1){
		if(NULL == head){
			printf("no product ,please wait,can sleep 2s\n");
			sleep(2);
			//等待
			pthread_cond_wait(&cond,&mutex);
		}
		else{
			//printf("start custom a product\n");
			//删除第一个节点
			temp=head;
			head =head->next;
			printf("消费者消费%d\n",temp->data);
			free(temp);
		}
	}
	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}

//生产者与消费者模型，条件变量的模型
int main(int argc,char ** argv){

	int ret=-1;
	srandom(getpid());
	//初始化条件变量
	ret = pthread_cond_init(&cond,NULL);
	if(0!=ret){
		printf("pthread_cond_init failed\n");
		return 1;
	}

	//初始化互斥锁
	ret = pthread_mutex_init(&mutex,NULL);
	if(0!=ret){
		printf("pthread_mutex_init failed\n");
		return 1;
	}

	//创建两个线程，生产者与消费者
	pthread_t tidp=-1,tidc=-1;

	//create thread of producer
	pthread_create(&tidp,NULL,producer,NULL);

	//create thread of customer
	pthread_create(&tidc,NULL,customer,NULL);


	//recycle  resource of two threads
	pthread_join(tidp,NULL);
	pthread_join(tidc,NULL);

	//销毁条件变量和互斥锁
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);

	return 0;
}
