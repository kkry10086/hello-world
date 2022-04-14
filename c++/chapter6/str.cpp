#include<iostream>
#include<string>
#include<vector>
//#include"str_split.h"
#include"fURL.h"

using std::cout;using std::cin;
using std::endl;
using std::string;
using std::vector;

int main(){
  string s;
  vector<string> v;
  /*split.h
  while(getline(cin,s)){
     v=split(s);


    for(vector<string>::size_type i=0;i!=v.size();i++)
	cout<<v[i]<<endl;
  }
  */
  //fURL.h
  while(getline(cin,s)){
    v.clear();
    v=URL(s);
     for(vector<string>::size_type i=0;i!=v.size();i++)
	cout<<v[i]<<endl;
  }
  

  return 0;

}
