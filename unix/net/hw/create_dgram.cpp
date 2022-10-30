/*用来生成报文的，tftp有六种
*/
#include<cstdio>
#include<cstring>
#include<arpa/inet.h>


#include<string>

using std::string;

//生成数据包
string get_dgram(short num,const char *buf){
    //转换成大端，在转为char*
    
    short tnum=(htons(num));
    //这里出问题，tnum的地址没有付给n
    //赋值给n没有问题.
    char *n=(char *)(&tnum);
    printf("tnum : %hd ,n[1]:%x\n",tnum,n[1]);
 
    char temp[strlen(buf)+5];
    printf("abc\n");
    printf("%s\n",buf);
    //这里除了问题，使用snprintf是temp要使用char var[size]而不是char *var;
    snprintf(temp,sizeof(temp),"03%c%c%s%c",n[0],n[1],buf,'\0');
    printf("abc\n");
    string ret=temp;   
    return ret;
}

//生成ACK
string get_ack(short num){
    //转换成大端，在转为char*
   short tnum=(htons(num));
    char *n=(char *)&tnum;
    string ret;
    ret.append("04");
    ret.append(n);
    return ret;
}

//生成ERROR
string get_error(short num,const char *buf){
    //转换成大端，在转为char*
    short tnum=(htons(num));
    char *n=(char *)&tnum;
    string ret;
    ret.append("05");
    ret.append(n);
    ret.append(buf);
    return ret;
}
