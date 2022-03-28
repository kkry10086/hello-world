#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<iomanip>
#include<ios>
#include<stdexcept>

using std::cout;using std::cin;
using std::endl;using std::string;
using std::sort;using std::max;
using std::vector;using std::istream;
using std::setw;using std::setprecision;
using std::streamsize;using std::domain_error;

struct Student_info{
	string name;
	double midterm,final;
	vector<double> homework;
};

//read student's homework grade
istream& read_hw(istream& in,vector<double>& hw){
	hw.clear();
	double x;
	cout<<"students' homework grade:"<<endl;
	while(in>>x){
		hw.push_back(x);
	}
	in.clear();
	return in;
}


//read student's grade
istream& read(istream& in,Student_info& s){
	cout<<"name midterm fianl:"<<endl;
	in>>s.name>>s.midterm>>s.final;
	if(in){
	read_hw(in,s.homework);}
	return in;
	
}

//how to sort students
bool mycomp(Student_info& i,Student_info& j){
	return i.name>j.name;

}
//return student's median one in homework grade
double grade(vector<double> vcd){
	typedef vector<double>::size_type vec_d;
	vec_d size=vcd.size();
	if(!size)return 0;
	vec_d mid=size/2;

	//sort student's homework grade by increased
	sort(vcd.begin(),vcd.end());

	//get the median one
	return size%2?vcd[mid]:(vcd[mid]+vcd[mid-1])/2;
}

//compute student's synthetic grade and return it
double grade(const Student_info& s){
	return 0.2*s.midterm+0.4*s.final+0.4*grade(s.homework);
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
	typedef vector<Student_info>::size_type vec_sz;
	vec_sz size=students.size();

	cout<<"students' xulie"<<endl;
	for(vec_sz i=0;i<size;i++){
		try{
			streamsize prec=cout.precision();
			cout<<setw(maxlen+1)<<students[i].name<<':'
				<<setprecision(3)<<grade(students[i])<<endl;
			setprecision(prec);
		}
		catch(domain_error e){
			cout<<e.what();
		}
	}

	return 0;


}

