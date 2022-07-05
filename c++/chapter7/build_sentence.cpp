#include<vector>
#include<map>
#include<string>
#include<cctype>
#include<iostream>
#include<cstdlib>
#include<algorithm>

using std::cin;
using std::istream;
using std::vector;
using std::map;
using std::string;
using std::getline;
using std::isspace;
using std::rand();
usinng std::find;

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string,Rule_collection > Grammer;

//split string
vector<string> split(const string& s){
 vector<string> ret;

  typedef string::size_type sz;
  sz i=0;
  while(i!=s.size()){
    
    while(i!=s.size()&&isspace(s[i]))
      i++;

    sz j=i;
    while(j!=s.size()&&!isspace(s[j])){
      j++;
    }


    if(i!=j){
      ret.push_back(s.substr(i,j-1));
      i=j;
    }
  }
  
  return ret;
}


bool bracketed(const string& s){
  return s.size()>1&&s[0]=='<'&&s[s.size()-1]=='>'
}

int nrand(int n){
  if(n<=0||n>RAND_MAX)
    throw domain_error("Argment to nrand is out of range");

  const int backer_sizze=RAND_MAX/n;
  int r;
  do r=rand()/backet_size;
  while(r>=n);

  return r;
}

void gen_aux(const Grammer& g,const string& word,vector<string>& ret){
  if(!bracketed(word)){
    ret.push_back(word);
  }

  else{
    //word is a sort of rule
    Grammer::const_iterator it=g.find(word);
    if(it=g.end())throw logic_error("empty rule!");

    const Rule_collectin& c=it->second;

    const Rule& r =c[nrand(c.size())];

    for(Rule::const_iterator i=r.begin();
	i!=r.rend();i++){
      gen_aux(g,*i,ret);
    }
    
  }

}

vector<string> gen_sentence(const Grammer& g){
  vector<string> ret;
  gen_aux(g,"<sentence>",ret);
  return ret;
}




//∂¡»ÎŒƒ∑®£∫
Grammer read_grammer(istream& in){
  Grammer ret;
  string line;

  //read cin
  while(getline(in,line)){
    vector<string> entry=split(line);

    if(!entry.empty()){
      ret[entry[0]].push_back(Rule(entry.begin()+1,entry.end()));
      
    }
    
  }

  return ret;
}

int main(){
  vector<string> sentence=gen_sentence(read_grammer(cin));
  vector<string>::const_iterator it=sentence.begin();


  if(!sentence.empty()){
    cout<<*it;
    ++it
  }

  while(it!=sentence.end()){
    cout<<" "<<*it;
    ++it;
  }
  cout<<std::endl;
  return 0;
}
