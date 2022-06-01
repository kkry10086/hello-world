#!/bin/bash
#Program:
#	Use id ,finger command to check system account's information
#History:
#2022/06/01	zcj	release 1
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:.
export PATH

users=$( cut -d ':' -f1 /etc/passwd )
for username in ${users}
do
	id ${username}
done
exit 0
