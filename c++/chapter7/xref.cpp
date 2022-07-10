#include<iostream>
#include<string>
#include<vector>
#include"xref.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(){
	//缺省使用split来调用xref
	map<string,vector<int> > ret=xref(cin);
	
	for(map<string,vector<int> >::const_iterator it=ret.begin();
			it!=ret.end();it++){
		cout<<it->first<<" occurs on line: ";
		vector<int>::const_iterator line_it=it->second.begin();
		cout<<*line_it;
		++line_it;

		while(line_it!=it->second.end()){
			cout<<" "<<*line_it;
			++line_it;
		}
		cout<<endl;
	}
	return 0;
}
