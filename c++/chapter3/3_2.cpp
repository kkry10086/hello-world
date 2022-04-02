/*title:
 *将输入的整数分为四部分，且排序为非递增排序
 * */

#include<iostream>
#include<vector>
#include<algorithm>
using std::cin;using std::cout;
using std::vector;using std::sort;
using std::endl;

bool mycomp(int i,int j){
    return (i>j);
}


int main(){
    //get some number
    cout<<"please enter Internumber:"<<endl;
    vector<int> list;
    int x;
    while(cin>>x)list.push_back(x);

    //sort list
    sort(list.begin(),list.end(),mycomp);

    typedef vector<int>::size_type vec_sz;
    vec_sz size=list.size();
    vec_sz len1=size/4+1;
    vec_sz len2=size/4;
    vec_sz i1=size%4;

    for(vec_sz i=0;i<i1;i++){
        for(vec_sz j=0;j<len1;j++)cout<<list[i*len1+j]<<' ';
	cout<<endl;
    }
    for(vec_sz i=i1;i<4;i++){
		vec_sz k=i-i1;
        for(vec_sz j=0;j<len2;j++){
		vec_sz node=i1*len1+k*len2+j;
		cout<<list[node]<<' ';
	}	
	cout<<endl;
    }

    return 0;
}
