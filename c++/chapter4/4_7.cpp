#include<iostream>
#include<vector>

using std::cout;using std::cin;
using std::endl;
using std::vector;

int main(){
	vector<double> dvc={1,8,95,65,78,5,65,45,52};
	double sum;
	vector<double>::size_type i=0;
	while(i<dvc.size()){
		sum+=dvc[i++];
	}
	cout<<sum/dvc.size()<<endl;
}
