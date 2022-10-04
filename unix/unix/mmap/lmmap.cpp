#include<string>
#include<iostream>

#include<unistd.h>
#include<cstring>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/wait.h>

using std::cin;using std::cout;
using std::endl;using std::string;

//父子进程使用匿名映射进行进程间通信
int main(){
  int ret=-1;
  pid_t pid=-1;
  void *addr=NULL;

  //1.创建匿名映射

  addr=mmap(addr, 1024, PROT_READ | PROT_WRITE,
	    MAP_SHARED | MAP_ANONYMOUS,-1,0);
  if(addr==MAP_FAILED){

    perror("mmap");
    return 1;
  }

    //2.创建子进程
  pid=fork();
  if(-1==pid){
    perror("fork");
    munmap(addr,1024);
    return 1;
  }

   //3.父子进程通信
  if(0==pid){
    //子进程写
    memcpy(addr,"9854673210",10);
    
  }
  else{
    //父进程读
    wait(NULL);
    cout<<(char *)addr<<endl;
  }



  //4.断开映射
  munmap(addr,1024);
  return 0;
}
