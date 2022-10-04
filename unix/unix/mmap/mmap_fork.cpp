#include<iostream>
#include<string>

#include<fcntl.h>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/wait.h>
using std::cin;using std::cout;
using std::endl;using std::string;

int main(int argc,char **argv){\

  int fd=-1;
  int ret=-1;
  int pid=-1;
  void *addr=NULL;
  
  //1.以读写的方式打开一个文件
  fd=open("txt",O_RDWR);
  if(-1==fd){
    perror("open");
    return 1;
  }

  //2.将文件映射到内存
  addr=mmap(addr,1024,PROT_READ|PROT_WRITE,MAP_SHARED,
	    fd,0);
  if(addr==MAP_FAILED){
    perror("mmap");
    return 1;
  }

  cout<<"文件映射到内存了"<<endl;

  //3.关闭文件
  close(fd);

  //4.创建一个进程
  pid=fork();

  if(-1==pid){
    perror("fork");
    return 1;
  }

  //子进程
  if(0==pid){
    //写文件
    memcpy(addr,"function",8);
  }
  else{
  
    //父进程
    wait(NULL);
    cout<<"addr:"<<(char *)addr<<endl;
    
  }
  
  munmap(addr,1024);
  return 0;
}
