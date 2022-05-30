#!/bin/bash
#Program:
#       Program shows the script name ,parameters...

#History:
#2022/05/30     zcj     release 1

PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH

echo " the script name is ==> $0"
echo " the number of parameters is ==> $#"
[ "$#" -lt 2 ] && echo "the number of parameters is less than 2. \
	Stop here. " && exit 0
echo "Your total parameters is ==> $@"

echo "The 1st parameters is $1"
echo "The 2nd parameters is $2"
