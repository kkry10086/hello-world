#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

//信号量变量
//容器个数
sem_t sem_producer;
//产品个数
sem_t sem_customer;

typedef struct _node_t{
	int data;
	struct _node_t *next;
}node_t;

node_t *head=NULL;

//thread of producer
void *producer(void *arg){
	while(1){
		//加锁
		//pthread_mutex_lock(&mutex);
		//申请一个容器资源
		sem_wait(&sem_producer);

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
		//pthread_mutex_unlock(&mutex);



		printf("producer produce %d \n",ne->data);
		//唤醒因为条件变量而阻塞的线程
		//pthread_cond_signal(&cond);

		//可消费的商品数加一
		sem_post(&sem_customer);
		sleep(1);

	}
	pthread_exit(NULL);
}

//thread of customer
void *customer(void *arg){
	//加锁
	//pthread_mutex_lock(&mutex);

	//申请资源，可以卖的商品个数减一
	sem_wait(&sem_customer);

	node_t *temp=NULL;
	while(1){
		if(NULL == head){
			printf("no product ,please wait\n");
			sleep(1);
			//等待
			//pthread_cond_wait(&cond,&mutex);
		}
		else{
			//printf("start custom a product\n");
			//删除第一个节点
			temp=head;
			head =head->next;
			printf("消费者消费%d\n",temp->data);
			free(temp);
			sleep(1);
			//商品容器数量加一

			sem_post(&sem_producer);
		}
	}

	//pthread_mutex_unlock(&mutex);
	//商品容器数量加一
	sem_post(&sem_producer);

	pthread_exit(NULL);
}

//生产者与消费者模型，条件变量的模型
int main(int argc,char ** argv){

	int ret=-1;
	srandom(getpid());
	//初始化信号量
	ret=sem_init(&sem_producer, 0, 4);
	if(0!=ret){
		printf("sem_init producer failed\n");
		return 1;
	}
	ret=sem_init(&sem_customer, 0, 0);
	if(0!=ret){
		printf("sem_init customer failed\n");
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

	//销毁信号量
	sem_destroy(&sem_producer);
	sem_destroy(&sem_customer);

	return 0;
}
