#include<cstdio>
#include<string>
//#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

//打开和关闭文件
int main(){

	int fd=-1;

	//只读的方式打开文件
	//fd=open("txt",O_RDONLY);
	
	//只写的方式打开文件
	//fd=open("txt",O_WRONLY|O_CREAT,0644);
	
        //只写的方式打开文件，如果文件存在就报错，如果文件不存在就新建一个文件
	//fd=open("txt",O_WRONLY |O_CREAT|O_EXCL,0644);
	
	//以读写的方式打开一个文件，如果文件存在就打开，不存在就新建一个文件
	//fd=open("txt",O_RDWR |O_CREAT,0644);
	
	//O_TRUNKC表示清空文件内容
	//fd=open("txt",O_WRONLY|O_TRUNC|O_CREAT,0644);	
	
	//O_APPEND以追加的方式
	//以只写和追加的方式打开文件，如果文件不存在出问题
	fd=open("txt",O_WRONLY | O_APPEND );
	if(fd==-1){
	
		perror("open");
		return 1;
	}

	printf("df = %d\n",fd);

	close(fd);
	return 0;
}
