#!/bin/bash
#Program:
#       Use function to repeat information
#History:
#2022/06/01     zcj     release 1
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH
function printit(){
	echo -n "Your choice is"
}
case ${1} in
	"one")
		printit; echo ${1}|tr 'a-z' 'A-Z'
		;;
	"two")
		printit; echo ${1}|tr 'a-z' 'A-Z'
		;;
	"three")
		printit; echo ${1}|tr 'a-z' 'A-Z'
		;;
	*)
		echo "Usage ${0} {one|two|three}"
		;;
esac
exit 0
