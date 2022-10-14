#include <iostream>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<unistd.h>
#include<signal.h>



using std::cout;using std::endl;

//信号响应函数
void fun(int signum){

  cout<<"捕捉到信号："<<signum<<endl;
}

int main(int argc,char ** argv){

    int ret=-1;
	struct itimerval tmo;

	//第一次触发的时间
	tmo.it_value.tv_sec=3;
	tmo.it_value.tv_usec=0;

	//触发周期
	tmo.it_interval.tv_sec=2;
	tmo.it_interval.tv_usec=0;
	
	//捕捉信号
	signal(SIGALRM,fun);

       //调用settimer函数
	
	//设置定时器，为自然时间
	ret=setitimer(ITIMER_REAL,&tmo,NULL);

    if(-1==ret){
		perror("settimer");
		return 1;
	}
	cout<<"按下任意键"<<endl;
	getchar();
	
	return 0;
}
