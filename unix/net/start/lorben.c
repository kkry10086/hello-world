#include<stdio.h>
#include<string.h>

#include<unistd.h>
typedef union std
{
  unsigned short a;
  unsigned char b[2];
}STD;

int main(int argc, char ** argv)
{
  STD tmp;
  tmp.a=0x0102;
  if(tmp.b[0] == 0x01){
    printf("big endian");
  }
  else{
    printf("litter endian");
  }
  

return 0;
}
