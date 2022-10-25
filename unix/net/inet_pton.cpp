#include<stdio.h>
#include<string>

#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>


using std::string;

int main(int argc, char ** argv)
{
  //char ip[]="192.168.1.2";
  unsigned int dst=0;

  if(argc!=2){
    printf("using a.out char*");
    return 1;
  }
  
  if(1!=inet_pton(AF_INET,argv[1],&dst)){
    printf("inet_pton failed");
    return 1;
  }
  printf("%d\n",dst);

  unsigned char *re = (unsigned char*)&dst;
  printf("ip: ");
  
  printf("%d",*re);
  for(int i=1;i<4;i++){
    printf(".%d",*(re+i));
  }
  printf("\n");
  

  
  
  return 0;
}
