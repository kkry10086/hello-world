#!/bin/bash
#Program:
#	Use for loop to print 3 animals
#History:
#2022/06/01	zcj	release 1
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH

for animal in dog cat elephant
do
	echo "There is a/an ${animal}"
done
exit 0

