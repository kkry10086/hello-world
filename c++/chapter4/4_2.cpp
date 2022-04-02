//compute square of num(1..100)
#include<iostream>
#include<iomanip>
#include<string>

using std::cout;using std::endl;
using std::setw;using std::to_string;

int main(){
	double lastn=100;
	unsigned len=to_string(int(lastn)).size();
    cout<<"1..100 µÄÆ½·½"<<endl;
    double i=1;
    while(i<=lastn){
	    cout<<setw(len)<<i<<':'<<i*i<<endl;
	    i++;
    
    }

}
