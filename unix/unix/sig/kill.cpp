#include <iostream>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<signal.h>
#include<unistd.h>

using std::cin;using std::cout;using std::endl;

//父进程杀死子进程
int main(int argc,char ** argv){
    
	pid_t pid=-1;
	pid=fork();
	
	if(-1==pid){
		perror("fork");
		return 1;
	}

	//子进程
	if(0==pid){
		while(1){
			cout<<"child  working..."<<endl;
			sleep(1);
		}
		exit(0);
	}

	//父进程
	else{
		sleep(3);
		cout<<"父进程终止子进程"<<endl;
		kill(pid,SIGTERM);
		cout<<"父进程也该结束了"<<endl;

	}
	return 0;
}
