#!/bin/bash
#Program:
#	Use ping command to check the network'c pc state 
#History:
#2022/06/01	zcj	release 1
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH

set intr=^C
#设置interrupt按键

network1=$( ifconfig wlp4s0 |grep "inet " |sed -e 's/ *inet'//g | sed -e 's/ *netmask.*//g'  )
echo -e "${network1} \n"
network="${network1%.[0-9]*}" 
echo -e "${network} \n "
for sitenu in $(seq 220 254)
do
	ping -c 1 -w 1 ${network}.${sitenu} &> /dev/null && result=0 || result=1

	if [ "${result}" == 0 ];then
		echo "server ${network}.${sitenu} is UP."
	else
		echo "sercer ${network}.${sitenu} is DOWN"
	fi
done

exit 0

