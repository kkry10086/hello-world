#include<iostream>
#include<string>
#include<vector>
#include "str_decorate.h"
#include "str_link.h"

using std::cin;using std::cout;
using std::endl;using std::string;
using std::getline;

int main(){
  string s;
  vector<string> v,top,below;

  while(getline(cin,s)){
    v.push_back(s);
  }
  top=decorate(v);
  /*
  cin.clear();
  while(getline(cin,s)){
    v.push_back(s);
  }
  below=decorate(v);
  */
  
  //  top=link(top,below);
  top=link2(v,top);
  vector<string> ::size_type i=0;
  while(i!=top.size()){
    cout<<top[i++]<<endl;
  }
  return 0;

}
