
#ifndef GUARD_str_link_h
#define GUARD_str_link_h

#include<vector>
#include<string>
#include "str_decorate.h"
using std::vector;
using std::string;




vector<string> link1(const vector<string>& top,const vector<string>& below)
{
  vector<string> ret=top;

  vector<string>::size_type i=0;

  while(i!=below.size()){
    ret.push_back(below[i]);
  i++;
  }
return ret;
 
  
}

vector<string> link2(const vector<string>& left,const vector<string>& right)
{
  vector<string> ret;

  string::size_type width1=width(left);

  vector<string>::size_type i=0,j=0;

  while(i!=left.size()||j!=right.size()){
    string s;
    if(i!=left.size())s=left[i++];

    s+=string(width1-s.size(),' ');

    if(j!=right.size())s+=right[j++];

    ret.push_back(s);
  }
  return ret;
  
}
#endif
