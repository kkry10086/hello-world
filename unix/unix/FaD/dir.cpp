#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>


#if 0
struct dirent {
	ino_t          d_ino;       /* Inode number */
	off_t          d_off;       /* Not an offset; see below */
	unsigned short d_reclen;    /* Length of this record */
	unsigned char  d_type;      /* Type of file; not supported
				       by all filesystem types */
	char           d_name[256]; /* Null-terminated filename */
};
#endif


int mkdir(char * dir){
	int ret=-1;
	ret=mkdir(dir,0755);
	if(-1==ret){
		perror("mkdir");
		return 1;
	}
	printf("创建目录成功\n");
	return ret;
}

char* ftype(unsigned char dtype){
	switch(dtype){
		case DT_REG:
			return (char*)"普通文件";
		case DT_DIR:
			return (char*)"目录";
		default:
			return (char*)"不知道";
	}
}

int main(int argc,char** argv){

	DIR* dir=NULL;
	struct dirent* d=NULL;

	if(argc!=2){
		printf("usage: process path\n");
		return 1;
	}
	//1.打开目录
	dir=opendir(argv[1]);

	if(NULL==dir){
		perror("opendir");
		//2.创建目录
		mkdir(argv[1]);
		dir=opendir(argv[1]);
		printf("打开目录成功...\n");
	}
	printf("打开目录成功...\n");

	//2.循环读取目录内容
	while(1){
		d=readdir(dir);
		if(NULL==d){
			perror("readdir");
			break;
		}
		char *ch=ftype(d->d_type);
		printf("ch:%s\n",ch);

		printf("d_type: %hu  d_name:%s\n",d->d_type,d->d_name);
	}




	//finally.close directory
	closedir(dir);

	return 0;	

}
