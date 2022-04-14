#ifndef GUARD_grade_h
#define GUARD_grade_h

#include"student.h"
#include<algorithm>
#include<numeric>

using std::accumulate;
using std::sort;



double median(const vector<double>& hw){
  sort(hw.begin(),hw.end());

  vector<double>::size_type mid=hw.size()/2;
  return hw.size()%2==0?(hw[mid]+hw[mid-1])/2:hw[mid];
       
}

double average(const vector<double>& hw){
  return accumulate(hw.begin(),hw.end(),0.0)/hw.size();
}


double grade(double midterm,double final,double hw){
  return 0.2*midterm+0.4*final+0.4*hw;
}

double grade(const Student_info s){
    return grade(s.midterm,s.final,median(s.homework));
  
}
double average_grade(const Student_info& s){
    return grade(s.midterm,s.final,average(s.homework));
}

bool fgrade(const Student_info& s){

  double stand_grade=60;
  
  if(grade(s)<stand_grade)
    return true;
  return false;
}



bool pgrade(const Student_info& s){
  return !fgrade(s);
}

#endif
