#!/bin/bash
#This shell script will create amount of linux login accounts for you
#1.check the "accountadd.txt" file exist?you must create that file munually
#  one account name one line in the "accountadd.txt"
#2.use openssl to create users passwd
#3.User must change his passwd in his first login
#4.more oprions check the following url
#History:
#2022/06/10	zcj	release 1

#0. userinput

usergroup=""   
# if you account need secondary group ,add here
pwmech="openssl"
#openssl or account is needed
homeperm="no"


#1.check the "accountadd.txt" file exist?you must create that file munually
#  one account name one line in the "accountadd.txt"
action=$1
if [ ! -f accountadd.txt ];then
	echo "There is no accountadd.txt"
	exit 1
fi
[ "${usergroup}" != "" ]&& groupadd -r ${usergroup}
rm -f outputpw.txt
usernames=$(cat accountadd.txt)

for username in ${usernames}
do
	case ${action} in
		"create")
			[ "${usergroup}" != "" ] && usegrp="-G ${usergroup}" ||
				usegrp=""
			useradd ${usegrp} ${username}
			[ "${pwmech}"=="openssl" ] && usepw=$(openssl rand -base64 6) || usepw=${username}
			#echo "${usepw}" | passwd --stdin ${username}
			echo "${username}:${usepw}" | chpasswd
			chage -d 0  ${username}
			[ "${homeperm}" == "yes" ] && chmod 711 /home/${username}
			echo "username=${username},passwd=${passwd}" >> outputpw.txt
			;;
		"delete")
			echo "deleting ${username}"
			userdel -r ${username}
			;;
		*)
			echo "Usage : $0 [create|delete]"
			;;
	esac
done




