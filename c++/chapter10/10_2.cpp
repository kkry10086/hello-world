#include<iostream>
#include<vector>
#include"copy.h"
#include"strlen.h"
#include<iterator>

using std::cout;using std::endl;
using std::vector;

int main(){
	const char he[]={'H','e','l','l','o'};
	vector<char> v;
	const char *it=(copy)(he,he+strlen(he),back_inserter(v));
	if(it!=he+strlen(he))
		cout<<"copy is failed"<<endl;
	else cout<<"copy is succeed"<<endl;

}
