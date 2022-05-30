#!/bin/bash
#Program:
#	This program show the first and last name you inputed ;
#History :
#2022/05/30	zcj	release 1
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH
read -p "Please input your first name : " firstname
read -p "Please input your last name : " lastname
echo  "\n yout full name is : ${firstname} ${lastname}"
exit 0


