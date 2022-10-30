#ifndef GURAD__create_dgram__h
#define GURAD__create_dgram__h

#include<string>

//生成数据包
std::string get_dgram(short num,const char *buf);

//生成ACK
std::string get_ack(short num);


//生成ERROR
std::string get_error(short num,const char *buf);

#endif