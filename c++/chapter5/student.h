
#ifndef GUARD_student_h
#define GUARD_student_h
#include<vector>
#include<string>
#include<iostream>
struct Student_info{
	std::string name;
	double midterm,final;
	std::vector<double> homework;
};

//read student's homework grade
std::istream& read_hw(std::istream& in,std::vector<double>& hw){


  if(in){
        hw.clear();
	double x;
	std::cout<<"students' homework grade:"<<std::endl;
	while(in>>x)
	  hw.push_back(x);
	if(in)std::cout<<"not"<<std::endl;
	in.clear();
	if(in)std::cout<<"yes"<<std::endl;

  }
	return in;
}

//read student's grade
std::istream& read(std::istream& in,Student_info& s){
	std::cout<<"name midterm fianl:"<<std::endl;
	in>>s.name>>s.midterm>>s.final;
	read_hw(in,s.homework);
	
	return in;
	
}
#endif
