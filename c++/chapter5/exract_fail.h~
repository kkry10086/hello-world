#ifndef GUARD_exract_fail_h
#define GUARD_exract_fail_h
#include<vector>
#include"student.h"
//#include"grade1.h"
#include"grade2.h"
using std::vector;

bool fgrade(const Student_info& s){
	if(grade(s)<60)return true;
	return false;
}

bool fgrade(vector<Student_info>::const_iterator iter){
	if(grade(*iter)<60)return true;
	return false;
}

vector<Student_info> exract_fials(vector<Student_info>& students){
	vector<Student_info> fail;
	
	/*It use index to take element
	vector<Student_info>::size_type i=0;

	while(i!=students.size()){
		if(fgrade(students[i])){
			fail.push_back(students[i]);
			students.erase(students.begin()+i);
		}
		i++;
	}
	*/

	//It use iterator to take element
	vector<Student_info>::iterator iteb=students.begin();


	while(iteb!=students.end()){
		if(fgrade(iteb)){
			fail.push_back(*iteb);
			iteb=students.erase(iteb);
		}
		else iteb++;
	}
	return fail;


}

#endif
