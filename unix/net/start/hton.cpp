#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(int argc, char ** argv)
{
 int num= 0x01020304;//小端
 short a= 0x0102;
  int sum = htonl(num);

  printf("%x\n",sum);

  short b= htons(a);
  printf("%x\n",b);
  
  return 0;
}
