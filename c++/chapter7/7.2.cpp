#include<map>
#include<string>
#include<iostream>

using std::map;using std::string;
using std::cin;using std::cout;
using std::endl;

int main(){
  string s;
  map<string,int> counters;//save every word and its num
  cout<<"please enter a few words"<<endl;

  while(cin>>s){
    ++counters[s];
  }

  for(map<string,int>::const_iterator it = counters.begin();
      it != counters.end();++it){

    cout<<it->first<<":\t"<<it->second<<endl;
  }

  cout<<"thanks for your using"<<endl;
  return 0;
}
