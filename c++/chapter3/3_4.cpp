#include<iostream>
#include<string>
#include<climits>

using std::cin;using std::cout;
using std::endl;using std::string;

int main(){
	//get the strings
    cout<<"please enter some strings:"<<endl;
    string temp_c;
    unsigned maxium,minum;
    maxium=0;minum=UINT_MAX;
    while(cin>>temp_c){
         if(temp_c.length()>maxium)maxium=temp_c.length();
	 else if(temp_c.length()<minum)minum=temp_c.length();
    }
    cout<<endl;
    cout<<"the longest one's length is "<<maxium
	    <<"the shortest one's length is "<<minum<<endl;

}
