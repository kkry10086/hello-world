
#include"student.h"
#include"grade.h"
//#include"write_analysis.h"
#include"extract_fails.h"
#include<iostream>
#include<vector>


using std::cout;using std::endl;
using std::cin;



bool did_all_hw(const Student_info& s){
  if (s.homework.size()<3)
    return false;
  return true;
}


int main(){
  Student_info s;
vector<Student_info> did,didnt;
  
  while(read(cin,s)){
    if(did_all_hw(s)){
      did.push_back(s);
    }
    else
      {
	didnt.push_back(s);
      }
   }
  if(did.empty()){
    cout<<"No student did all hw"<<endl;
  }
  if(didnt.empty()){
    cout<<"Every student did all hw"<<endl;
  }
  //compute median_analysis
 // write_analysis(cout,"median",median_analysis,did,didnt);

  //compute average_analysis
  //write_analysis(cout,"average",average_analysis,did,didnt);

  //did.insert(did.begin(),did.end(),didnt.begin());

  // or copy(didnt.begin(),didnt.end(),back_inserter(did.end()));
  //vector<Student_info> fails=extract_fails(did);

  


  
  return 0;
  
}
