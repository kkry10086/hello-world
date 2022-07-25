#include<fstream>
#include<string>
#include<iostream>

using std::cout;using std::endl;
using std::ifstream;using std::ofstream;

int main(int argc, char ** argv)
{
	int fail_count=0;
	for(int i=1;i<argc;++i)
	{
		ifstream infile(argv[i]);
		if(infile){
			std::string s;
			while(getline(infile,s))
				cout<<s<<endl;
		}
		else
		{
			std::cerr<<"cannot open file"<<argv[i]<<endl;
			++fail_count;
		}
	}
	return fail_count;
}
