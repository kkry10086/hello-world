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

	//2.文件描述符复制
	//fcntl返回一个最小的可用的且大于等于第三个参数的文件描述符
	newfd=fcntl(fd,F_DUPFD,0);
	if(-1==newfd){
		perror("fcntl");
		return 1;
	}
	printf("newfd:%d\n",newfd);

	write(fd,"12890234",8);
	write(newfd,"Abcdfe",6);

	close(fd);
	close(newfd);
}

