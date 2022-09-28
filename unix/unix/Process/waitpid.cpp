#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	pid_t pid=-1;
	int  status;

	pid=fork();

	if(-1==pid){
		perror("fork");
		return 1;
	}
	if(0==pid){
		for(int i=0;i<3;i++){
		printf("child process%d  do thing %d \n",getpid(),i+1);
		sleep(1);
		}
		exit(0);
	}
	printf("父进程等待子进程退出，回收资源\n");

	//int ret=waitpid(pid,&status,0);
	//与wait一样
	
	int ret=waitpid(pid,&status,WNOHANG);
	//不阻塞情况下
	if(-1==ret){
	perror("wait");
	return 1;
	}
	printf("父进程回收子进程的资源\n");
	if(WIFEXITED(status)){
	printf("子进程推出码: %d\n",WEXITSTATUS(status));
	}
	else if(WIFSIGNALED(status)){
		printf("子进程退出码：%d \n",WTERMSIG(status));
	}
	else if(WIFSTOPPED(status)){
		printf("子进程退出码： %d\n",WSTOPSIG(status));
	}
	return 0;
}
