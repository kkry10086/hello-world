#include<cstddef>
#include"strlen.h"
#include"copy.h"
using std::size_t;

char * duplicate_chars(const char *p)
{
	//allocate enough memory especially '\0'
	size_t length=strlen(p)+1;
	char *result =new char[length];
	std::copy(p,p+length,result);
	return result;
}
