
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<iomanip>
#include<ios>
#include<stdexcept>
//#include"grade.h"
#include"exract_fail.h"

using std::cout;using std::cin;
using std::endl;using std::string;
using std::sort;using std::max;
using std::vector;using std::istream;
using std::setw;using std::setprecision;
using std::streamsize;using std::domain_error;



//how to sort students
bool mycomp(Student_info& i,Student_info& j){
	return i.name>j.name;

}


int main(){
	vector<Student_info> students;
	Student_info record;
	string::size_type maxlen=0;

	//save all datas of student's grade,and find the largest length
	cout<<"please enter studnets' grade:"<<endl;

	while(read(cin,record)){
		maxlen=max(maxlen,record.name.size());
		students.push_back(record);
	}

	//sort student by their name
	sort(students.begin(),students.end(),mycomp);
	
	
	/*this is copied from 5-1.cpp,don't mind
	typedef vector<Student_info>::size_type vec_sz;
	vec_sz size=students.size();

	cout<<"students' xulie"<<endl;
	for(vec_sz i=0;i<size;i++){
		try{
			streamsize prec=cout.precision();
			cout<<setw(maxlen+1)<<students[i].name<<':'
				<<setprecision(3)<<grade(students[i])<<endl;
*/
	//the program is that I change 
	for(vector<Student_info>::const_iterator iter = students.begin();
			iter!=students.end();iter++){
		cout<<(*iter).name<<endl;
	}
	return 0;



}
