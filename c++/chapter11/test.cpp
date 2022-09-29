#include"Vec.h"
#include<iostream>

using std::cout;using std::cin;
using std::endl;

int main(){
	int x;
	Vec<int> vv;
	cout<<"请输入10个整数："<<endl;
	for(int i=0;i<10;++i){
		cin>>x;
		vv.push_back(x);
	}
	cout<<vv.size()<<endl;
	Vec<int>::const_iterator it=vv.begin();
	while(it++!=vv.end()){
		cout<<*it;
	}
	cout<<endl;
}
