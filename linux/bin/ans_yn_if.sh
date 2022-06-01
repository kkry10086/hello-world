#!/bin/bash
#Program:
#	This program shows the user's choice
#History:
#2022/06/01	zcj	release 1
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH

read -p "Please input [y/n] : " yn

if [  -z "${yn}" ]; then 
	echo "You must input your choice ."
	exit 0
fi

if [ "${yn}" == "Y" -o "${yn}" == "y" ]; then
	echo "Ok,continue"
	exit 0
fi
if [ "${yn}" == "N" ] || [ "${yn}" == "n" ]; then
	echo "Oh,interrupt"
	exit 0
fi

echo "I don't know what your choice is " && exit 0
