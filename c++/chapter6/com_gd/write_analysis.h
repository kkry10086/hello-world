#ifndef GUARD_write_analysis_h
#define GUARD_write_analysis_h


#include<stdexcept>
#include<iostream>
#include<algorithm>
#include"student.h"
#include"grade.h"

using std::endl;
using std::cin;
using std::ostream;
using std::transform;
using std::domain_error;


double grade_aux(const Student_info& s){
  try{
    return grade(s);
  }
  catch(domain_error){
    return grade(s.midterm,s.final,0);
  }
}



double median_analysis(const vector<Student_info>& v){
  vector<double> grades;
  transform(v.begin(),v.end(),back_inserter(grades),grade_aux);
  return median(grades);
}



double average_analysis(const vector<Student_info>& v){
  vector<double> grades;
  transform(v.begin(),v.end(),back_inserter(grades),average_grade);
  return median(grades);
  
}



void write_analysis(ostream& cout,string method,
		    double analysis(const vector<Student_info>&),
		    const vector<Student_info>& did,
		    const vector<Student_info>& didnt){

  cout<<method<<"did:"<<analysis(did)<<" didnt:"<<analysis(didnt)<<endl;
  return;
}


#endif
