#!/bin/bash
#Program:
#	User input a filename,program will check the flowing:
#	1.)exit? 2.)file/directory 3.)file permissions

#History:
#2022/05/30	zcj	release 1

PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

echo "Please input a filename, I will check the filename'type and permissions"
read -p "Input a filename : " filename

test -z ${filename} && echo "You must input a string" && exit 0
test ! -e ${filename} && echo "the filename : ${filename} does NOT exit" && exit 0
test -f ${filename} && filetype="regular file"
test -d ${filename} && filetype="directory"
test -r ${filename} && perm="readable"
test -w ${filename} && perm="${perm} writable"
test -x ${filename} && perm="${perm} executable"

echo "The filename : ${filename} is a ${filetype}"
echo "And the permisions for you are : ${perm}"


