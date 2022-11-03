#ifndef GUARD__WRAP_H
#define GUARD__WRAP_H

#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<iostream>
#include<string.h>


int Accept(int fd,struct sockaddr *sa,socklen_t *salenptr);
int Bind(int fd,struct sockaddr * addr,socklen_t len);
int Tcp4_bind(short port,const char *ip);
#endif
