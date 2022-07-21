
#include<iostream>
#include"Student_info.h"
#include<algorithm>
#include<ios>
#include<iomanip>
#include<stdexcept>
using std::cin;using std::cout;
using std::endl;using std::domain_error;
using std::sort;using std::max;
using std::setprecision;using std::streamsize;

int main(){
	vector<Student_info> students;
	Student_info record;
	string::size_type maxlen=0;
        //record students' data 
	while(record.read(cin)){
		maxlen=max(maxlen,record.name().size());
		students.push_back(record);
	}
        //sort students by name
	sort(students.begin(),students.end(),compare);

	//print name and grade
	for(vector<Student_info>::size_type i=0;
			i!=students.size();++i){
		cout<<setw(maxlen+1)<<students[i].name();
		try{
			double final_grade=students[i].grade();
			streamsize prec =cout.precision();
			cout<<setprecision(3)<<final_grade
				<<setprecision(prec)<<endl;
		}catch(domain_error e){
			cout<<e.what()<<endl;
		}
	}
	return 0;
}
