#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<cctype>

using std::cin;using std::cout;
using std::endl;using std::map;
using std::string;
using std::vector;
using std::geline;
using std::space;

/*
int main(){
  string s;


 
  map<string,int> counters;

  while(cin>>s){
    counters[s]++;
  }
  for(map<string,int>::const_iterator it=counters.begin();
      it !=counters.end();++it){
    cout<<it->first<<"\t"<<it->second<<endl;
  }
  return 0;
}
*/

vector<string> split(const string& s){
  vector<string> ret;

  typedef string::size_type sz;
  sz i=0;
  while(i!=s.size()){
    
    while(i!=s.size()&&isspace(s[i]))
      i++;

    sz j=i;
    while(i!=s.size()&&!isspace(s[j])){
      j++;
    }


    if(i!=j){
      ret.push_back(s.substr(i,j-1));
      i=j;
    }
  }

  return ret;
    
}


map<string,vector<int> > xref(istream& in,
			      vector<string> find_words(const string&)=split){

  string line;
  int line_num=0;

  map<string,vetor<int> > ret;

  while(getline(in,line)){
    line_num++;
    vector<string> words=find_words(line);
    for(vector<string>::const_iterator it=words.begin();
	it!=words.end();it++){
      ret[*it].push_back(line_num);
    }
  }
  return ret;
}

int main(){
  map<string,vector<int> > str_line;
  str_line=xref(cin,split);

  
  return 0;
}

