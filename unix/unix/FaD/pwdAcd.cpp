#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define SIZE 32
int main(){
	//1.获取当前进程的工作目录
	char buf[SIZE];
	int ret=-1;

	if(NULL==getcwd(buf,SIZE)){
		perror("getcwd");
		return 1;
	}
	printf("pwd:%s\n",buf);


	//2.改变当前的工作目录
	
	ret=chdir("/home/kali");
	if(-1==ret){
		perror("chdir");
		return 1;
	}
	//3.获取当前的工作目录
	memset(buf,0,SIZE);
	if(NULL==getcwd(buf,SIZE)){
		perror("getcwd");
		return 1;
	}
	printf("pwd:%s\n",buf);

	
}


