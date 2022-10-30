#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include "create_dgram.h"
#include "download.h"

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






//判断操作码
// int analys(char *buf){
//      //请求下载的
//     if('0'==buf[0] && '1'==buf[1]){
//         return 1;
//     }
//     //请求上传的
//     if('0' == buf[0] && '2' == buf[1]){
//         return 2;
//     }
//     //DGRAM数据包
//     if('0'==buf[0] && '3'==buf[1]){
//         return 3;
//     }
//     //ACK
//     if('0'==buf[0] && '4'==buf[1]){
//         return 4;
//     }
//     //ERROR
//     if('0'==buf[0] && '5'==buf[1])
//     {
//         return 5;
//     }
//     //操作码错误的
//     else{
//         return 0;
//     }


// }






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
        sendD(talk_sock,buf,cli);
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
         
    close(talk_sock);
}





