#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
//#include<iomanip>

using std::cout;using std::cin;
using std::endl;using std::string;
using std::vector;using std::sort;
//using std::setw;

int strPrint(vector<string> strs){
	if(strs.empty()){
		cout<<"you don't enter any string"<<endl;
		return -1;
	}
	sort(strs.begin(),strs.end());

	typedef vector<string>::size_type s_size;

	s_size size=strs.size();
	s_size t=0;
	while(t<size){
		cout<<strs[t]<<' ';
		t++;
	}
	//vector<unsigned> list;

	s_size i=0;
	s_size j=i+1;
	vector<string>::iterator begin=strs.begin();
	unsigned num=1;
	while(i<size){
		if(j<size&&strs[i]==strs[j]){
			strs.erase(begin+j);
			size=strs.size();
			num++;
		}
		else {
			//list.push_back(num);
			cout<<strs[i]<<':'<<num<<endl;
			i++;
			j=i+1;
			num=1;
		}

	}
	return 0;


}



int synthetise(vector<string>& strs){
	cout<<"please enter string:"<<endl;
	strs.clear();
	cin.clear();

	string x;
	while(cin>>x){
		strs.push_back(x);
	}

	return strPrint(strs);
	


}


int main(){
	vector<string> str;
	return synthetise(str);


}
