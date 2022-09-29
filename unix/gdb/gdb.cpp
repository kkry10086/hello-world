#include<iostream>

using std::cin;using std::endl;
using std::cout;

void fun(){

	int i=0;
	for(;i<10;++i){
	
		cout<<"fun-->"<<i<<endl;
	}
}

int main(int argc,char* argv[]){

	fun();
	cout<<"argv.length:"<<argc<<endl;
	for(int i=0;i<argc;++i){
	
		cout<<"argv["<<i<<"]: "<<argv[i]<<endl;
	}
	return 0;
}
