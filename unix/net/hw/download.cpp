/*当tftp是下载时，应该怎么做
*/
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>


#include<vector>
#include<string>

#include"create_dgram.h"


using std::string;
using std::vector;


#define SIZE 512

//重传最大次数
#define send_recv_num 10

//等待报文最长时间，决定为100毫秒
#define wait_time 100

//决定关闭连接的报文的差错码
const short close_num=03;

//判断操作码
int analys(char *buf){
     //请求下载的
    if('0'==buf[0] && '1'==buf[1]){
        return 1;
    }
    //请求上传的
    if('0' == buf[0] && '2' == buf[1]){
        return 2;
    }
    //DGRAM数据包
    if('0'==buf[0] && '3'==buf[1]){
        return 3;
    }
    //ACK
    if('0'==buf[0] && '4'==buf[1]){
        return 4;
    }
    //ERROR
    if('0'==buf[0] && '5'==buf[1])
    {
        return 5;
    }
    //操作码错误的
    else{
        return 0;
    }


}


//打开文件，返回fd
int open_file(const char *buf){
    int fd = -1;
    fd = open(buf,O_RDONLY);
    return fd;
    
}

vector<string> str_tok(char *buf){
    printf("str_tok s\n");
     vector<string> vec_str;

    //以0作为分割符号，将buf分割为多个数组，
    //并转换为string类。
    char split ='\0';
    char *word = strtok(buf,&split);
    while(NULL != word){
        vec_str.push_back(word);
        word = strtok(NULL,&split);
    }
    printf("str_tok e\n");
    return vec_str;
}



//收到的报文操作码为1的情况下
//10/27现在不考虑有OACK的情况
//发送数据包
int sendD(int& sock,char *buf,struct sockaddr_in *cli){
    
    
    //将数据根据'\0'分割，赋值给vec_str，buf+2将操作码去掉
    vector<string> vec_str = str_tok(buf+2);

 
    //vec_str[0]是文件名
    //打开文件
    const char *filename =vec_str[0].c_str();
    printf("fn:%s\n",filename);
    int fd = open_file(filename);
    //如果fd小于0,就返回05的ERROR报文
    if(fd < 0){
        printf("%s  : 文件不存在\n",filename);
        string a;
        const char *msg=a.append("文件不存在").c_str();
        //使用ERROR操作码返回
        string ret = get_error(close_num,msg);
        sendto(sock,ret.c_str(),ret.length()+1,0,
               (struct sockaddr*)cli,sizeof(*cli));
        //退出
        return -1;
    }
    //文件打开了
    //vec_str[1]是模式，假设都是octet
    //那么就可以直接传输数据
    //传输数据用的字符串;
    char msg[SIZE];
    memset(msg,0,SIZE);

    //块编号
    short num=1;
    //n等于读到的字节数
    int n = -1;
    while((n=read(fd,msg,SIZE-1)) > 0){
        //printf("msg:%s : len :%d\n",msg,strlen(msg));
        msg[SIZE-1]='\0';
        
        //这里出问题了，在这里有问题
        string ret = get_dgram(num,msg);
        printf("%s\n",ret.c_str());

        //传输的次数n
        // int frequency = 0;
        
    
        sendto(sock,ret.c_str(),ret.length()+1,0,
                (struct sockaddr*)cli,sizeof(*cli));

        // char *temp = inet_ntoa((*cli).sin_addr);
        // printf("af:%d port:%d ip:%s \n",
        //    (*cli).sin_family,ntohs((*cli).sin_port),temp);
            

            //当frequency达到
            // frequency++;
            
            
            //发送了数据，接下来就等待结果
            //但是要结果到达，判断是否为ack,不是就重新发送。
            //或者对方决定要关掉连接(先不做)
            char recv[SIZE];
            //我们已经有客户端的socket信息：cli
            recvfrom(sock,recv,SIZE,0,NULL,NULL);

        
        sleep(1);
        memset(msg,0,SIZE);

        num++;

    }
       if( SIZE == n ){
            memset(msg,0,SIZE);
            msg[0] = '\0';
            string ret = get_dgram(num,msg);
             sendto(sock,ret.c_str(),ret.length()+1,0,
                   (struct sockaddr*)cli,sizeof(cli));
        }
    close(fd);
    return 0;    
        
}

//解析数据包中快编号的函数
short get_sequence(char *buf){
    //buf前两个是操作码，之后两个是快编号，最后都是数据
    char temp[2]={buf[2],buf[3]};
    short ret = *(short *)temp;
    return ntohs(ret); 

}


//接受数据包
int receiveD(int &sock){

    //交互结构体
    struct sockaddr_in talk_addr;
    //接受数据
    char rbuf[516] ="";

     int n = -1;

    socklen_t addrlen=sizeof(talk_addr);


   //以只写打开文件,清空内容，没有文件就创建
   int fd = open("/home/kali/unix/net/hw/newnew.cpp",O_WRONLY|O_CREAT|O_TRUNC ,0644);
   if( fd < 0){
    perror("open");
    return 1;
   }


  printf("while\n");
  
  memset(&talk_addr,0,sizeof(talk_addr));

  //对方也有可能没有接收到第一个报文,但现在不管
  while(1){   

    memset(rbuf,0,sizeof(rbuf));
     printf("rbuf\n");
    
    
    //10/29这里有问题，
    recvfrom(sock,rbuf,516,0,(struct sockaddr *)&talk_addr,&addrlen);
    printf("recev:%c%c\n",rbuf[0],rbuf[1]);

    //判断操作码
    //接收到的是数据包的报文，将数据写入新建文件
    if( 3 == analys(rbuf)){
         //由于数据包中前两个字节是操作码，后面是快编号，最后都是数据。
        short num= get_sequence(rbuf);
        
        //写入文件
        n = write(fd,rbuf+4,sizeof(rbuf)-4);

        

         //发送ack给对方
         string sbuf = get_ack(num);
         sendto(sock,sbuf.c_str(),sizeof(sbuf.c_str()),0,(struct sockaddr *)&talk_addr,sizeof(talk_addr));
          //接收到的数据小于SIZE，数据发送完毕，结束传输
         if(n<SIZE){
            break;
         }
         
    }
    else{
        //没有接收到相应的数据包的报文，不写入
        printf("没有接收到03的报文");
        string sbuf = get_ack(0);
        sendto(sock,sbuf.c_str(),sizeof(sbuf.c_str()),0,(struct sockaddr *)&talk_addr,sizeof(talk_addr));

    }

  }
  close(fd);
  return 0;


}
