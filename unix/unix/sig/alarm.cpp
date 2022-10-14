#include <iostream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

using std::cout;
using std::endl;

int main(int argc,char ** argv){
    
	unsigned int seconds=0;

	//第一次设置闹钟，5秒钟后超时，
	//发送SIGALRM 信号
	seconds=alarm(5);

	cout<<"上一次闹钟剩下的时间："<<seconds<<endl;
    
	sleep(2);
	//之前没有超时的闹钟被新的闹钟覆盖了
	seconds=alarm(5);
	cout<<"上次闹钟剩下的时间："<<seconds<<endl;


	cout<<"按下任意值继续"<<endl;
	getchar();

	return 0;
}
