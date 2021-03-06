#ifndef GUARD_student_h
#define GUARD_student_h


#include<vector>
#include<string>
#include<iostream>

using std::vector;
using std::string;
using std::istream;

struct Student_info{
  string name;
  double midterm,final;
  vector<double> homework;
};

istream& readhw(istream& in, vector<double>& hw){
  hw.clear();
  std::cout<<"please enter your hw:"<<std::endl;
  double x;
  while(in>>x){
    hw.push_back(x);
  }
  in.clear();
  clearerr(stdin);

  return in;
}

istream& read(istream& in,Student_info& s){
  in.clear();
  std::cout<<"name,midterm,final:"<<std::endl;
  in>>s.name>>s.midterm>>s.final;

  if(in){
    readhw(in,s.homework);
  }
  return in;
}

#endif
