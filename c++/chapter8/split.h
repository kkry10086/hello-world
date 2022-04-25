#ifndef GUARD_split_h
#define GUARD_split_h

#include<string>
#include<cctype>

using std::isspace;


bool space(const char& c){
  return isspace(c);
}
bool no_space(const char& c){
  return !space(c);
}

using std::string;


template<class out>
void split(const string& str,out os){
  typedef string ::const_iterator citer;

  citer i=str.begin();

  while(i!=str.end()){
    i=find_if(i,str.end(),no_space);
    
    citer j=find_if(i,str.end(),space);

    if(i!=str.end())
      *os++=string(i,j);

    i=j;

  }
}


#endif
