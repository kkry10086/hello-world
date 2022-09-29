#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<cstdlib>
//区分父子进程
int main(){
	pid_t pid=-1;

	pid=fork();
	if(pid<0){
		printf("fork 失败");
		return 0;
	}

	if(0==pid){
		//子进程
		printf("这里是子进程:pid: %d  ppid: %d \n",getpid(),getppid());

		exit(0);
	}
	else{
		//父进程
		printf("这里是父进程:pid:%d cpid:%d \n",getpid(),pid);
	

	}
	return 0;

}
