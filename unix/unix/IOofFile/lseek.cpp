#include<cstdio>
#include<string>
//#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define SIZE 128
//打开和关闭文件
int main(){

	int fd=-1;
	int ret=-1;
	char buf[SIZE];

	fd=open("txt",O_RDWR | O_CREAT,0644);
	if(fd==-1){
	
		perror("open");
		return 1;
	}

	printf("df = %d\n",fd);

	//lseek操作
	write(fd,"abcdefghi",9);
	
	ret=lseek(fd,18,SEEK_SET);

	if(-1==ret){
		perror("lseek");
		return 1;
	}
	write(fd,"1234567890",10);
	ret=lseek(fd,0,SEEK_SET);
	ret=read(fd,buf,SIZE);

	printf("buf:%s\n大小:%d",buf,ret);

	close(fd);
	return 0;
}

