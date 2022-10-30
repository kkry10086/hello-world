#ifndef GUARD__download__H
#define GUARD__download__H
//发送数据包
int sendD(int& sock,char *buf,struct sockaddr_in *cli);
//接受数据包
int receiveD(int &sock);

//分析数据的操作码
int analys(char *buf);

#endif