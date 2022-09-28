#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(void){
	pid_t pid=-1;
	pid_t ppid=-1;

	//获取当前进程号
	pid=getpid();

	printf("进程号:%d\n",pid);

	//获取当前进程的父进程号
	ppid=getppid();
	printf("父进程号：%d\n",ppid);

	//获取当前进程的进程组号
	pid=getpgid(pid);
	printf("当前进程的进程组号:%d\n",pid);
	return 0;
}
