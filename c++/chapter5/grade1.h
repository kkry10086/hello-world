#ifndef GUARD_grade1_h
#define GUARD_grade1_h

//topic : This program is my first time write down to 
//        resolve how to compute synthetic grade .
//        So I used index before i learn iterator.  
//

#include<vector>
#include<iostream>
#include<algorithm>
#include"student.h"
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
	return size%2?vcd[mid]:(vcd[mid]+vcd[mid+1])/2;
	
}

//compute student's synthetic grade and return it
double grade(const Student_info& s){
	return 0.2*s.midterm+0.4*s.final+0.4*grade(s.homework);
}
#endif
