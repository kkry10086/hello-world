#ifndef GUARD_STUDENT_H
#define GUARD_STUDENT_H

#include<istream>
#include<vector>
#include<string>
using std::istream;
using std::string;
using std::vector;

class Student_info{

	public:
		Student_info();
		Student_info(std::istream&)
		double grade() const;
		std::istream& read(std::istream&);
		std::string name() const{return n;}
		bool valid() const{return !homework.empty();}
	private:
		std::string n;
		double midterm,final;
		std::vector<double> homework;
};
Student_info::Student_info():midterm(0),final(0){}
Student_info::Student_info(istream& is){rean(is);}

istream& Student_info::read(istream& in){
	in>>name>>midterm>>final;
	::read_hw(in,homework);
	return in;
 }
double Student_info::grade()const{
	return ::grade(midtern,final,homework);
}
bool compare(const Student_info& ,const Student_info&);

#endif
