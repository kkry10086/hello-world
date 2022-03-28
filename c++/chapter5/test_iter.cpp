#include<vector>
#include<iostream>

using std::vector;using std::cout;using std::endl;

int main(){
	vector<double> vec={1,2,3,4,5,6,7,8,9};
	vector<double> :: iterator iter=vec.begin(),i1=iter+1,i2=iter+2;
	cout<<"first:"<<endl;
	cout<<"iter: "<<*iter<<", i1: "<<*i1<<", i2: "<<*i2<<endl;
	iter=vec.erase(iter);
	cout<<"second:"<<endl;
	cout<<"iter: "<<*iter<<", i1: "<<*i1<<", i2: "<<*i2<<endl;
	return 0;

}
