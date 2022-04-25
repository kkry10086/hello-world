#include<iostream>
#include<iterator>
#include<algorithm>
#include<vector>

using std::cout;
using std::cin;
using std::istream_iterator;
using std::ostream_iterator;
using std::copy;


int main(){
  std:: vector<int> v;
  copy(istream_iterator<int>(cin),istream_iterator<int>(),back_inserter(v));

  copy(v.begin(),v.end(),ostream_iterator<int>(cout," "));


  
}
