#ifndef GUARD_median_h
#define GUARD_median_h

#include<vector>
#include<iostream>
using std::vector;
using std::endl;
using std::cout;

//return student's median one in homework grade
double grade(vector<double> vcd){
      cout<<"filename: median"<<endl;
	typedef vector<double>::size_type vec_d;
	vec_d size=vcd.size();
	if(!size)return 0;
	vec_d mid=size/2;

	//sort student's homework grade by increased
	sort(vcd.begin(),vcd.end());

	//get the median one
	return size%2?vcd[mid]:(vcd[mid]+vcd[mid-1])/2;
}
#endif
