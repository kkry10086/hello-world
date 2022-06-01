#!/bin/bash
#Program:
#	This program shows the effect of shift function
#History:
#2022/05/31	zcj	release 1

PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH

echo "Toal Parameter number is ==> $#"
echo "Your whole parameter is ==> $@"

shift #进行第一次［一个变量的ｓｈｉｆｔ］
echo "first one is ==> $1"
echo "Toal Parameter number is ==> $#"
echo "Your whole parameter is ==> $@"

shift 3 #进行第二次［一个变量的ｓｈｉｆｔ］

echo "first one is ==> $1"
echo "Toal Parameter number is ==> $#"
echo "Your whole parameter is ==> $@"
