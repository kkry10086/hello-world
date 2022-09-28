#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


//孤儿进程：父进程退出了，子进程还在执行
int main(){
	pid_t pid=-1;
	pid=fork();

	if(-1==pid){
		perror("fork");
		return 1;
	}
	if(pid>0){
		printf("父进程休息一秒...\n");
		sleep(1);
		printf("父进程推出....\n");
		exit(0);
	}
	while(1){
		printf("子进程不停的工作 ppid=%d pid=%d \n",getppid(),getpid());
		sleep(1);
	}
	return 0;
}
