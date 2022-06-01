#!/bin/bash
#Program:
#	check $1 is equal to "hello"
#History:
#2022/06/01	zcj	release 1
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH

if [ "$1" == "hello" ];then 
	echo "Hello, how are you"
elif [ -z "$1" ];then
	echo "You must input parameters ,ex > { ${0} someword }"
else
	echo "The only parameter is 'hello',ex {${0} someword}"
fi
exit 0
	
