#include<iostream>
#include"letter_grade.h"
#include"strlen.h"
#include<cstddef>

using std::cout;using std::endl;
using std::size_t;

int main(){
	static const double le[]={
	99,55,66,88,44,22,0,0,1,3};
	size_t nle=strlen(le);
	for(size_t i=0;i<nle;++i){
		cout<<letter_grade(le[i])<<"  ";
	}
	cout<<endl;
}

