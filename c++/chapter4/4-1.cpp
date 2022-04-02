#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<ios>
#include<iomanip>
#include<stdexcept>

using std::cout;using std::cin;
using std::endl;using std::string;
using std::vector;using std::sort;
using std::setprecision;
using std::streamsize;
using std::domain_error;
using std::istream;

//function of reading homework grades
istream& read_hw(istream& in,vector<double>& hw){
   if(in){
	   //clear the sence in homework
	   hw.clear();

	   //read homework
	   double x;
	   while(in>>x)hw.push_back(x);

	   //clear istream for the next reading 
	   in.clear();

   } 
    return in;

}

//function of compute median grade
double median(vector<double> hw){
	sort(hw.begin(),hw.end());
	typedef vector<double>::size_type vec_sz;
	vec_sz size=hw.size();
	vec_sz mid=size/2;
	return size%2==0?(hw[mid]+hw[mid-1])/2:hw[mid];
}

//function of compute synthetical grade
double grade(double midterm,double final,const vector<double>& hw){
	if(hw.size()==0)
		throw domain_error("student has done no homework");
	return 0.2*midterm+0.4*final+0.4*median(hw);
}


int main(){

	cout<<"Please enter yout first name: ";
	string name;
	cin>>name;
	cout<<"Hello ,"<<name<<"!"<<endl;
	
	//ask for midterm and final exam grades
	cout<<"ask for midterm and final exam grades: ";
	double midterm,final;
	cin >> midterm>>final;

	//ask for homework grades
	cout<<"Enter all your homework grades: ";
	vector<double> homework;

	//function of reading homework grades
	read_hw(cin,homework);

	//compute the synthetical greade
	
	try{
		double syn_grade=grade(midterm,final,homework);
		streamsize prec=cout.precision();
		cout<<"your synthetical grade is "<<setprecision(3)<<syn_grade
			<<setprecision(prec)<<endl;

	}
	catch(domain_error){
		cout<<endl<<"You must enter your grades."
			<<"Please try again."<<endl;
		return 1;
	}
	return 0;


}
