#include<iostream>
#include<unistd.h>

using std::cout;using std::endl;

int main(int argc, char** argv){

  cout<<"输入终端："<<ttyname(0)<<endl;
  cout<<"输出终端："<<ttyname(1)<<endl;
  cout<<"错误输出终端："<<ttyname(2)<<endl;

  return 0;
}
