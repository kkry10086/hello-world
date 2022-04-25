#include<string>
#include<algorithm>
#include<iostream>
#include<iterator>
#include"split.h"

using std::string;
using std::copy;
using std::cin;
using std::cout;
using std::ostream_iterator;

int main(){
  string s;
  while(getline(cin,s)){
    split(s,ostream_iterator<string>(cout,"\n"));
    
  }
  return 0;
}
