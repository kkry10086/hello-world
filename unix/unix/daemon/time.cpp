#include<iostream>
#include<string>


#include<time.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

using std::cout;using std::endl;
using std::string;using std::to_string;
#define  SIZE 128
int main(int argc, char** argv){

  time_t t=-1;
  struct tm *lT=NULL;
  char filename[SIZE];

  //获取时间，秒为单位
  t=time(NULL);

  if(-1==t){
    perror("time");
    return 1;
  }

  lT=localtime(&t);
  if(NULL==lT){
    cout<<"localTime failed"<<endl;
    return 1;
  }
  cout<<"当前时间,t:"<<t<<endl;
  cout<<"ctime:"<<ctime(&t)<<endl;

  cout<<"localTime:"<<lT->tm_year+1900<<"-"<<lT->tm_mon+1<<"-"<<lT->tm_mday;
  cout<<" "<<lT->tm_hour<<":"<<lT->tm_min<<":"<<lT->tm_sec<<endl;
  /*
  string s=string(to_string(lT->tm_year+1900));
  s.append("-");s.append(to_string(lT->tm_mon+1));
   s.append("-");s.append(to_string(lT->tm_mday));
   s.append(" ");s.append(to_string(lT->tm_hour));
   s.append(":");s.append(to_string(lT->tm_min));
   s.append(":");s.append(to_string(lT->tm_sec));
  cout<<"ssss:"<<s<<endl;
  */
  memset(filename,0,SIZE);
  sprintf(filename,"%s%d-%d-%d %d:%d:%d.log'","touch '/tmp/",
	  lT->tm_year+1900,lT->tm_mon+1,lT->tm_mday,
	  lT->tm_hour,lT->tm_min,lT->tm_sec);
  cout<<filename<<endl;

  system(filename);
  
  return 0;
}
