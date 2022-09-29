#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc,char** argv){

	int fd=fd=-1;
	int newfd=-1;

	fd=open("txt",O_RDWR | O_CREAT,0644);
	if(-1==fd){
		perror("open");
		return 1;
	}
	printf("fd: %d\n",fd);
	//dup2的内容
        newfd=2;
	newfd=dup2(fd,newfd);

	//newfd=dup(fd);
	if(-1==fd){

		perror("dup2");
		return 1;
	}

	printf("fd: %d\n",fd);
	printf("newfd: %d\n",newfd);

	write(fd,"abcdefg",7);
	write(newfd,"123456789",9);

	close(fd);
	close(newfd);




	return 0;

}
