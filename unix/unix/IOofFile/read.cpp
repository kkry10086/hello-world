#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

#define SIZE 128

int main(){

	int fd=-1;
	int ret=-1;
	char buf[SIZE];
	

	fd=open("txt",O_RDONLY);
	if(fd ==-1){
	
		perror("open");
		return -1;
	}
	printf("fd = %d\n",fd);

	//清空字符串
	memset(buf,0,SIZE);

	ret =read(fd,buf,SIZE);
	if(ret==-1){
		perror("read");
		return -1;
	}

	printf("read len: %d\n",ret);
	printf("txt: %s",buf);
	close(fd);
	return 0;

}
