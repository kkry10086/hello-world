#GUARD_xref_h
#DEFINE_xref_h

//#include<iostream>
#include<string>
#include<vector>
#include<map>

using std::string;using std::vector;
using std::map;using std::getline;

map<string,vector<int> > xref(istream& in,
		vector<string> find_words(const string& )=split)
{
	string line;
	int line_num=0;
	map<string,vector<int> > ret;
	while(getline(in,line)){
		++line_num;

		//split the sentence
		vector<string> words=find_words(line);
		//remember every word in the sentence now
		for(vector<string>::const_iterator it=words.begin();
				it!=words.end();++it){
			ret[*it].push_back(line_num);
		}
	}

	return ret;
}

#endif
