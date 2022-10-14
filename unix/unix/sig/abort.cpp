#include <iostream>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>

using std::cout;
using std::endl;

int main(int argc,char ** argv){
    
	int i=1;

	while(1){
		cout << "do working " << i <<endl;

		if(4 == i){
			//给自己发送一个编号为6的信号，默认的行为就是终止自己
			abort();
		}
		i++;
		sleep(1);
	}
	return 0;
}
