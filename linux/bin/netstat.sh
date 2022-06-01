#!/bin/bash
#Program:
# 	Using netstat and grep to detect WWW,SSH,FTP,MAIL services
#History:
#2022/06/01	 zcj	release 1
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH	

echo "Now ,I will detect your linux server's services !"
echo "The www,ftp,ssh,mail will be detect !" 

testfile=/dev/shm/netstat_checking.txt
netstat -tunl > ${testfile}
testing=$(grep ":80" ${testfile})
if [  "${testing}" != "" ];then
	echo "WWW is running in your system"
fi

testing=$(grep ":22" ${testfile})
if [  "${testing}" != "" ];then
	echo "SSH is running in your system"
fi

testing=$(grep ":21" ${testfile})
if [ "${testing}" != "" ];then
	echo "FTP is running in your system"
fi

testing=$(grep ":25" ${testfile})
if [ "${testing}" != "" ];then
	echo "MAIL is running in your system"
fi

exit 0
