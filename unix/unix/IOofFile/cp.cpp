#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>


#define SIZE 128
int main(){

	int fd1=-1;
	int fd2=-1;
	int rnum=-1;
	char buf[SIZE];

	char  iname[10], oname[10];
	

	printf("请输入要被复制的文件的名称:");
	scanf("%s",iname);
	printf("请输入要复制出来的文件的名称:");
	scanf("%s",oname);


	fd1=open(iname,O_RDONLY);
	fd2=open(oname,O_WRONLY |O_CREAT,0644);

	if(fd1==-1){
		perror("open");
		return 1;
	}
	if(fd2==-1){
		perror("write");
		return 1;
	}

	while((rnum=read(fd1,buf,SIZE))!=0){
		printf("传输的数据：%d\n",rnum);
		write(fd2,buf,rnum);
	}

	return 0;
	


}
