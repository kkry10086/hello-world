#ifndef GUARD_LETTER_GRADE_H
#define GUARD_LETTER_GUARD_H
#include<string>
#include<cstddef>

using std::size_t;

std::string letter_grade(double grade){
	//broadcast of grade
	static const double numbers[]={97,
	94,90,87,84,80,77,74,70,60,0};
	//letter_grade inflect to grade of number
	static const char* const  letters[]={"A+",
	"A","A-","B+","B","B-","C+","C","C-","D","F"};

	static const size_t ngrades=sizeof(numbers)/sizeof(*numbers);
	for(size_t i=0;i<ngrades;++i){
		if(grade>=numbers[i])
			return letters[i];
	}
	return "?\?\?";


}

#endif
