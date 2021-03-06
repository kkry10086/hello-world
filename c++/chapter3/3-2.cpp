#include<algorithm>
#include<iomanip>
#include<ios>
#include<iostream>
#include<string>
#include<vector>
using std::cin;using std::cout;
using std::endl;using std::string;
using std::vector;using std::setprecision;
using std::streamsize;using std::sort;

int main(){
    //ask for student's name
    cout<<"please enter your name:";
    string name;
    cin>>name;
    cout<<"Hello, "<<name<<endl;

    //get the midterm and final grade
    cout<<"Please enter your midterm and final grade";
    double midterm,final;
    cin>>midterm>>final;

    //ask for student's score of homework
    cout<<"Enter all your homework grades"<<endl;

    vector<double> homework;
    double x;

    //save grades in vector named homework
    while(cin>>x){
        homework.push_back(x);
    }

    //check homework whether is null
    typedef vector<double>::size_type vec_sz;
    vec_sz size =homework.size();
    if(size==0){
	    cout<<"you must enter your homework,"
		    <<"please try again."<<endl;
	    return 1;
    }
    //sort homework
    sort(homework.begin(),homework.end());

    //compute the mid grade
    vec_sz mid=size/2;
    double median=(size%2==0)?(homework[mid-1]+homework[mid])/2:homework[mid];

    //return the synthesis grade
    streamsize prec=cout.precision();
    cout<<"your synthesis grade is"<<setpricision(3)<<0.2*midterm+0.4*final+0.4*median<<endl;
    setprecision(prec);
    return 0;
}
