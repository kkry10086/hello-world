#include<iostream>
#include<cstddef>
#include<vector>
#include"copy.h"
using std::size_t;using std::vector;
using std::cout;using std::endl;

int main(){
	const size_t NDim = 3;
	double coords[NDim]={1,2,3};
	vector<double> v;
	(copy)(coords,coords+NDim,back_inserter(v));
	for(vector<double>::size_type i=0;i<v.size();i++){
		cout<<v[i]<<"   ";
	}
	cout<<endl;
}
