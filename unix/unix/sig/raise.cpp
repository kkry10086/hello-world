#include <iostream>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>

using std::cin;using std::cout;
using std::endl;

int main(int argc,char ** argv){

    int i=0;
	while(1){
		cout<<"do working "<<i<<endl;
		//自己给自己发信号
		if(i==4){
			//自己给自己发送编号15的信号
			raise(SIGTERM);
		}
		i++;
		sleep(1);
	}
	return 0;
}
