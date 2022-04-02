#include<iostream>
//#include<string>
//#include<vector>
#include"str_split.h"

//using std::string;
//using std::vector;
using std::cout;using std::cin;
using std::getline;
using std::endl;



int main(){

	string s;
	cout<<"请输入一段字符串："<<endl;
	while(getline(cin,s)){
		vector<string> v=split(s);
		cout<<"a vector is be returned"<<endl;

		for(vector<string>::size_type i=0;
				i!=v.size();++i)
			cout<<v[i]<<endl;
	}
	return 0;

}
