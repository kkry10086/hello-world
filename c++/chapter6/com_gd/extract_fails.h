#ifndef GUARD_extracts_fails_h
#define GUARD_extracts_fails_h


#include"student.h"
#include"grade.h"
#include<algorithm>


//using std::remove_copy_if;
//using std::remove_if;
//using std::stable_partition;



//vector<Student_info> extract_fails(vector<Student_info>& students){
  //vector<Student_info> fails;

  //remove_copy_if(students.begin(),students.end(),
		// back_inserter(fails),pgrade);
 // students.erase(remove_if(students.begin(),students.end(),fgrade),students.end());
  //remove_if put elements that satify fgrade after that do not,
  //then return the begin element of that satisfied; 
 // return fails;
//}

//vector<Student_info> pextract_fails(vector<Student_info>& students){
  //vector<Student_info>::iterator iter=
    //stable_partition(students.begin(),students.end(),
		  //   pgrade);
  //vector<Student_info> fails(iter,students.end());
  //students.erase(iter,students.end());

  //return fails;
  
//}




#endif
