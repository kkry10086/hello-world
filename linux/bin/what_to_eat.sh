#!/bin/bash
#Program:
#	Choose what to eat
#History:
#2022/06/02	zcj	realese 1
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH
eat[1]="麦丹劳"
eat[2]="肯德基"
eat[3]="彩虹"
eat[4]="牛杂"
eat[5]="闹钟"
eat[6]="老板"
eat[7]="便利店"
eat[8]="章鱼"
checksum=8
check=$((${RANDOM}*${checksum}/32767+1))
echo "You may eat ${eat[${check}]}"
