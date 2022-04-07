#include<iostream>
#include<algorithm>
#include<vector>
#include<string>


using std::cin;using std::cout;
using std::endl;
using std::copy;using std::max;
using std::vector;using std::string;
using std::getline;

int main(){
  vector<string> v1,v2;
  string s;

  cout<<"first picture to write"<<endl;
  while(getline(cin,s)){
    v1.push_back(s);
  }
  /*
  cout<<"second picture to write"<<endl;
  
  while(getline(cin,s)){
    v2.push_back(s);
  }
  */

  for(vector<string>::size_type i=0;i!=v1.size();++i){
    cout<<v1[i]<<endl;
  }
  
  for(vector<string>::size_type i=0;i!=v2.size();++i){
    cout<<v2[i]<<endl;
  }

	
}
