//错误处理函数

#include<cstdio>
#include<cerrno>
#include<cstring>
#include<unistd.h>

int main(){

	//打开文件
	FILE *fp=fopen("txt","r");
	if(fp == NULL){
		printf("fopen failed...\n");
		printf("errno:%d\n",errno);
		//根据errno解析出错的原因
		printf("fopen:%s\n",strerror(errno));


		//根据errno值输出错误信息
		perror("fopen");

	        sleep(100);

		return 1;
			
	}

	sleep(100);
	return 0;
}
