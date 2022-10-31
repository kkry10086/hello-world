#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc, char ** argv)
{

   unsigned int dst=0;

  if(argc!=2){
    printf("using ./a.out string");
    return 1;
  }
  
  if(1!=inet_pton(AF_INET,argv[1],&dst)){
    printf("inet_pton failed");
    return 1;
  }

  char np[INET_ADDRSTRLEN] = "";
  inet_ntop(AF_INET,&dst,np,INET_ADDRSTRLEN);
  printf("ip:%s\n",np);
  
  
return 0;
}
