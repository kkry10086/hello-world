#ifndef GUARD_lineC_h
#define GUARD_lineC_h

#include<string>
#include<vector>
#include<map>


using std::map;
using std::vector;
using std::string;using std::getline;
using std::istream;




map<string,vector<int> > xref (istream& in,
			       vector<string> find_words(const string&)=split){

  string line;
  int line_number=0;
  map<string,vector<int> > ret;

  while(getline(in,line)){
    ++line_number;

    //split line in words
    vector<string> words=find_words(line);

    //rember word in line,its number plus 1
    for(vector<string>::const_iterator it=words.begin();
	it!=words.end();it++){
      ret[*it].push_back(line_number);
    }

  }
  return ret;

}


#endif
