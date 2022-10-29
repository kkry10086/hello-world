#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

//这里是c++的头文件
#include <string>
#include <vector>
#include <chrono>

using std::string;
using std::vector;

#define SIZE 512
//重传最大次数
#define send_recv_num 10

//等待报文最长时间，决定为100毫秒
#define wait_time 100

//决定关闭连接的报文的差错码
const short close_num=03;


//获得当前时间毫秒
//std::chrono::illiseconds getmicrotime(){
//    std::chrono::milliseconds ms = std::chrono:duration_cast<
//        std::chrono::milliseconds >(
//            std::chrono::system_clock::now().time_since_epoch()
//            );
//    return ms;
//}

//打开文件，返回fd
int open_file(const char *buf){
    int fd = -1;
    fd = open(buf,O_RDONLY);
    return fd;
    
}

//生成数据包
string get_dgram(short num,const char *buf){
    //转换成大端，在转为char*
    char *n=(char *)(htons(num));
    string ret;
    ret.append("03");
    //append会把最后的'\0'自动删掉
    ret.append(n);
    ret.append(buf);
    return ret;
}

//生成ACK
string get_ack(short num){
    //转换成大端，在转为char*
    char *n=((char *)htons(num));
    string ret;
    ret.append("04");
    ret.append(n);
    return ret;
}

//生成ERROR
string get_error(short num,const char *buf){
    //转换成大端，在转为char*
    char *n=(char *)(htons(num));
    string ret;
    ret.append("05");
    ret.append(n);
    ret.append(buf);
    return ret;
}


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





//收到的报文操作码为1的情况下
//10/27现在不考虑有OACK的情况
int one(int sock,char *buf,struct sockaddr_in *cli){
    vector<string> vec_str;

    //以0作为分割符号，将buf分割为多个数组，
    //并转换为string类。vec_str[0]是文件名
    char *word = strtok(buf+2,0);
    while(NULL != word){
        vec_str.push_back(word);
        word = strtok(NULL,0);
    }

    //vec_str[0]是文件名
    //打开文件
    int fd = open_file(vec_str[0].c_str());
    //如果fd小于0,就返回05的ERROR报文
    if(fd < 0){
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
    while((n=read(fd,msg,SIZE)) >= 0){

      
        //如果等于0,就将msg置为0
        if( 0 == n ){
            memset(msg,0,SIZE);
            msg[0] = '\0';
        }
        
        string ret = get_dgram(num,msg);

        //传输的次数n
        int frequency = 0;
        
        //设置开始时间
        //long fs = getmicrotime();
        do{
            sendto(sock,ret.c_str(),ret.length()+1,0,
                   (struct sockaddr*)cli,sizeof(*cli));
            

            //当frequency达到
            frequency++;
            //比较现在与开始时间的差别，如果时间大于100毫秒就
            //发送03ERROR报文关闭连接
            /*
            反正udp不保证传输的数据的完整性，丢了也不管，所以也就懒得写了
            if((getmicrotime()-fs) >= wait_time){
                break;
            }
            */
            
            //发送了数据，接下来就等待结果
            //但是要结果到达，判断是否为ack,不是就重新发送。
            //或者对方决定要关掉连接(先不做)
            char recv[SIZE];
            //我们已经有客户端的socket信息：cli
            recvfrom(sock,recv,SIZE,0,NULL,NULL);

            //获得ack证明对方接收到了，继续
            if( 4 == analys(recv)){
                break;
            }
            
        
        }
        while(frequency < send_recv_num);

        num++;

    }
    return 0;    
        
}

//这里就是将buf与sockaddr_in获得并进行交流
void server_talk(char *buf,struct sockaddr_in *cli)
{
    //新建一个用来专门和cli交流的socket
    int talk_sock = socket(AF_INET,SOCK_DGRAM,0);
    string ret;
    
    

    //第一次受到信息，只可能是收到1/2的，
    //其他就发送ERROR操作码的报文回去
    int ana=analys(buf);
    switch (ana){
    case 1:
        ret.clear();
        ret= "03analys == 1";
        printf("%d    %s\n",ana,ret.c_str());
        sendto(talk_sock,ret.data(),ret.length(),0,
               (struct sockaddr *)cli,sizeof(*cli) );
        break;
    case 2:
        ret.clear();
        ret= "03analys == 2";
        printf("%d    %s\n",ana,ret.c_str());
        sendto(talk_sock,ret.data(),ret.length(),0,
               (struct sockaddr *)cli,sizeof(*cli) );
        break;
    default:
        ret.clear();
        ret = "0501操作码错误";
        printf("%d    %s\n",ana,ret.c_str());
        sendto(talk_sock,ret.data(),ret.length(),0,
               (struct sockaddr *)cli,sizeof(*cli) );
        break;
        
    }
         
}





