#!/bin/bash
#Program:
#	Use loop to calaulate result of "1+2+3+...+100"
#History:
#2022/06/01	zcj	release 1
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH
s=0
i=1
while [ "${i}" != "101" ]
do
	s=$(($s+$i))
	i=$(($i+1))
done
echo "The result of '1+2+...+100' is ==> $s"
