#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<cstdlib>
#include<cstring>
//区分父子进程的地址空间

int num=100;
//存储在数据段中
int main(){
	pid_t pid=-1;

	int var =8;
	//存储在栈中
	int *p=NULL;
	int x=512;
	int *p1=&x;

	pid=fork();

	p=(int*)malloc(sizeof(int));
	//在堆区分配内存空间
	
	if(NULL ==p ){
		printf("malloc failed");
		return 1;
	}
	memset(p,0,sizeof(int));
	(*p)=200;

	if(-1==pid){
		perror("fork");
		return 1;
	}

	if(0==pid){
		//子进程
		sleep(1);
		printf("子进程: var:%d num: %d *p:%d \n *p1=%d ", var,num,*p,*p1);
	        free(p);
	        p=NULL;	
	}
	else{
		//父进程
		printf("父进程: var:%d num=%d *p:%d *p1=%d \n", var,num,*p,*p1);
		var++;
		num++;
		(*p)++;
		(*p1)++;
		printf("父进程: var:%d num=%d *p:%d *p1=%d \n", var,num,*p,*p1);
	
	        free(p);
	        p=NULL;	

	}
	return 0;

}
