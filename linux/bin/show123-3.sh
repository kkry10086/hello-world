
#!/bin/bash
#Program:
#       Use function to repeat information
#History:
#2022/06/01     zcj     release 1
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH
function printit(){
	echo -en "Your choice is ${1} \n"
}
case ${1} in
	"one")
		printit 1
		;;
	"two")
		printit 2
		;;
	"three")
		printit 3
		;;
	*)
		echo "Usage ${0} {one|two|three}"
		;;
esac
exit 0
