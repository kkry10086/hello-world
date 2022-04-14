
#include<string>
#include<vector>
#include<cctype>
#include<algorithm>

using std::string;
using std::vector;
using std::isspace;
using std::find_if;

bool space(char c){
  return  isspace(c);
}

bool not_space(char c){
  return !isspace(c);
}


vector<string> split(const string& s){

	vector<string> ret;
	typedef string::const_iterator iter;
	iter i=s.begin();

	while(i!=s.end()){
	  //ignore blank before all words

	  i=find_if(i,s.end(),not_space);

	  iter j=i;
	  //find a blank after any word
	  j=find_if(j,s.end(),space);

	  //copy a word between i and j,push_back ret
	  if(i!=s.end())
	    ret.push_back(string(i,j));//left close and right is open

	  i=j;
	}
	return ret;

	
	/*I copy it from chapter5/str_sp,and i changed it.

        typedef string::size_type str_sz;
	str_sz i=0;


	while(i!=s.size()){
		while(i!=s.size()&&isspace(s[i]))++i;

		str_sz j=i;
		while(j!=s.size()&&!isspace(s[j]))++j;

		while(i!=j){
			ret.push_back(s.substr(i,j-i));
			i=j;
		}

	}
	
	return ret;
	*/
}
