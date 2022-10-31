#include<stdio.h>
#include<string.h>

#include<unistd.h>
#include<arpa/inet.h>
int main(int argc, char ** argv)
{

  //da                 //xiao
  int num= 0x01020304;//大端
  short a= 0x0102;

  int sum = htonl(num);
  printf("%x\n",ntohl(sum));

  short b = htons(a);
  printf("%x\n",ntohs(b));

  return 0;
}
