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
eatsum=8
eated=0
while [ "${eated}" -lt 3 ]
do
	check=$((${RANDOM}*${eatsum}/32767+1)) 
	mycheck=0
	if [ "$eated" -ge 1 ];then
		for i in $(seq 0 "${eated}")
		do
			if [ "${eatedcon[$i]}" == "${eat[${check}]}" ];then
				mycheck=1
			fi
		done
	fi
	if [ ${mycheck} == 0 ];then
		echo "you may eat ${eat[${check}]}"
		eatedcon[${eated}]=${eat[${check}]}
		eated=$((${eated}+1))
	fi

done

