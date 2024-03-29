#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

//fcntl复制文件描述符

int main(){
	int fd=-1;
	int newfd=-1;
	int ret=-1;

	//1.打开文件
	fd=open("txt",O_RDWR |O_CREAT,0644);
	if(-1==fd){
		perror("open");
		return 1;
	}
	printf("fd:%d\n",fd);

	//2.获取文件状态的标记
	ret=fcntl(fd,F_GETFL);
	if(-1==ret){
		perror("fcntl");
		return 1;
	}
	if(ret & O_APPEND){
		printf("before has append\n");
	}
	else{
		printf("before has not append\n");
	}

	//3.设置文件状态标记
	ret=ret | O_APPEND;
	ret=fcntl(fd,F_SETFL,ret);
	if(-1==ret){
		perror("fcntl");
		return 1;
	}

	//4.获取文件状态的标记
	ret=fcntl(fd,F_GETFL);
	if(-1==ret){
		perror("fcntl");
		return 1;
	}
	if(ret & O_APPEND){
		printf("before has append\n");
	}
	else{
		printf("before has not append\n");
	}


	close(fd);
	close(newfd);
}

