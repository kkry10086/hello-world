#!/bin/bash
#Program:
#	Show "hello" from $1... by using case ..esac
#History:
#2022/06/01	zcj	release 1
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH

case ${1} in
	"hello")
	       echo "Hello, how are you?"
	       ;;
       "")
               echo "You MUST input parameters ,ex > {${0} someword}"
               ;;

	*)
		echo "usage {$0 hello}"
		;;
esac
