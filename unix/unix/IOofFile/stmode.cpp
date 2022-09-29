#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

//显示文件类型的第一个版本，不建议
/*
int show_file_type(struct stat &s){
	switch(s.st_mode & S_IFMT){
		case S_IFREG:
			printf("普通文件");
			break;

		default:
			printf("其他类型");
			break;

	}
	return 0;
}
*/
int show_file_type(struct stat &s){
	if(S_ISDIR(s.st_mode)){
	
		printf("Directory\n");
	}

	return 0;

}

//显示文件权限

int show_permission(struct stat& s){
	int p=0;

	//判断文件所属者权限
	if(s.st_mode & S_IRUSR){
		p+=400;
	}
	if(s.st_mode & S_IWUSR){
		p+=200;
	}
	if(s.st_mode & S_IXUSR){
		p+=100;
	}
	if(s.st_mode & S_IRGRP){
		p+=40;
	}
	if(s.st_mode & S_IWGRP){
		p+=20;
	}
	if(s.st_mode & S_IXGRP){
		p+=10;
	}
	if(s.st_mode & S_IROTH){
		p+=4;
	}
	if(s.st_mode & S_IWOTH){
		p+=2;
	}
	if(s.st_mode & S_IXOTH){
		p+=1;
	}


	return p;
	
}

//获取文件类型与权限
int main(int argc,char** argv){
	int ret=-1;
	struct stat s;
	if(2!=argc){
		printf("usage:./aout filename\n");
		return 1;
	}



	ret=stat(argv[1],&s);
	if(-1==ret){
		perror("stat");
		return 1;
	}

	show_file_type(s);
	int res=show_permission(s);
	printf("权限是： %d\n",res);

	return 0;

}
