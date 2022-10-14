#include <iostream>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<unistd.h>

using std::cout;using std::endl;

int main(int argc,char ** argv){

    int ret=-1;
	struct itimerval tmo;

	//第一次出发的时间
	tmo.it_value.tv_sec=3;
	tmo.it_value.tv_usec=0;

	//出发周期
	tmo.it_interval.tv_sec=2;
	tmo.it_interval.tv_usec=0;

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
