#include<iostream>
using std::cout;using std::endl;
int main(int argc,char**argv){
	if(argc>1){
		int i;
		for(i=1;i<argc-1;++i)
			cout<<argv[i]<<" ";
		cout<<argv[i]<<endl;
	}
	return 0;
}
