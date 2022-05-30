#!/bin/bash
#Program:
#	This program shows the user's choice

#History:
#2022/05/30	zcj	release 1

PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:../bin
export PATH

read -p "Please input [y/n] :" yn
[ -z "${yn}" ] && echo "You must input your choice" && exit 0
[ 'Y' == "${yn}" -o 'y' == "${yn}" ] && echo "OK,continue;" && exit 0
[ 'N' == "${yn}" -o "n" == "${yn}" ] && echo "Oh,interrupt;" && exit 0
echo " I don't know what your choice is" && exit 0


