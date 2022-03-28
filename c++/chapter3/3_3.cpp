/*this program is used to count the numbers of char in statements
 * */


#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using std::cin;using std::cout;
using std::endl;using std::string;
using std::vector;using std::sort;
bool mycomp(string i,string j){
	if(i==j)return 1;
	else return 0;
}


int main(){
	cout<<"please enter a statement:";
	string x;
	vector<string> ct_ch;
	
	while(cin>>x)ct_ch.push_back(x);
        //justice whether it is empty
	if(ct_ch.empty()){
		cout<<"what you write in is empty, "
			<<"try again please."<<endl;
		return 1;
	}

	typedef vector<string>::size_type vec_sz;
	vec_sz size =ct_ch.size();

	vector<unsigned> num_c;
		
	for(vec_sz i = 0;i<size-1;i++){
		unsigned x=1;
		for(vec_sz j =i+1;j<size;){
			if(ct_ch[i] == ct_ch[j]){
				x++;
				ct_ch.erase(ct_ch.begin()+j);
	                        size =ct_ch.size();
				
			}
			else j++;
		}
		num_c.push_back(x);
	
	}
	
	typedef vector<unsigned>::size_type u_sz;
	u_sz usize = num_c.size();
	for(u_sz i = 0;i<usize;i++){
		cout<<ct_ch[i]<<':'<<num_c[i]<<endl;
	}




    return 0;
}
