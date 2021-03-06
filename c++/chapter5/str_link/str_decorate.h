
#ifndef GUARD_str_decorate_h
#define GUARD_str_decorate_h

#include<vector>
#include<string>
#include<iostream>

using std::vector;
using std::string;
using std::cout;using std::endl;

string ::size_type width(const vector<string>& v){

  vector<string>::size_type i=0;
  string ::size_type maxlen=0;
  while(i!=v.size()){
    if(v[i].size()>maxlen)maxlen=v[i].size();
    i++;
    
  }
  return maxlen;
}


vector<string>  decorate(const vector<string>& v){

  vector<string> ret;
  string::size_type maxlen=width(v);

  
  vector<string>::size_type i=0;
  string border(maxlen+4,'*');

  ret.push_back(border);

  while(i!=v.size()){
    ret.push_back("* "+v[i]+string(maxlen-v[i].size(),' ')+" *");
    i++;
  }

  ret.push_back(border);
  return ret;
  

}

#endif
