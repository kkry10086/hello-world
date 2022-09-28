#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<unistd.h>

int main(){
	printf("hello world!");
	_exit(0);
	//equal to _Exit(0); 
	//这个不会刷新缓冲区,不会关闭文件描述符,所以不会输出数据
	//就是不会做事后清理工作

	//	exit(0);

	//equal to return(0)
	//
	
	//return 0;
}
