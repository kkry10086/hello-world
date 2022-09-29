#include<cstdio>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main(){

	int fd=-1;
	int ret=-1;
	char* str="write success";

	fd=open("txt",O_WRONLY | O_CREAT,0644);
	if(fd ==-1){
	
		perror("open");
		return 1;
	}
	printf("fd= %d\n",fd);

	ret=write(fd,str,strlen(str));
	if(ret==-1){
	
		perror("write");
		return 1;
	}

	printf("write len: %d\n",ret);
	close(fd);
	return 0;
}
