#include<iostream>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>

using std::cout;using std::cin;


//创建守护进程
int main(int argc, char ** argv){

  int ret=-1;
  pid_t pid=-1;
  time_t t;

  //1.创建子进程，父进程退出
  pid=fork();
  if(-1==pid){
    perror("fork");
    return 1;
  }
  if(pid>0){
    //父进程退出
    exit(0);
  }

  //2.创建新的会话，完全脱离控制终端

  pid=setsid();
  if(-1==pid){
    perror("setsid");
    return 1;
  }

  
  //3.改变当前工作目录
  ret=chdir("/");
  if(-1==ret){
    perror("chdir");
    return 1;}

  //4.设置权限掩玛
  umask(0);
  
  //5.关闭文件描述符
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  

  //6.执行守护进程
  //每个一秒钟输出当前时间到/tmp/txt.log文件中
  //p160有关于头文件的查看

  while(1){
    //获取当前时间，以秒为单位
    t=time(NULL);
    sleep(3);
    //system("date >> /tmp/txt.log");
    system("touch \"/tmp/$(date +\"%Y-%m-%d %H:%M:%S\").txt\"");
  }

  return 0;
}
