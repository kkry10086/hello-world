#!/bin/bash
#Program:
#User inputs 2 integer numbers;program will cross these two numbers
#
#History:
#2022/05/30	zcj	release 1

PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

echo -e "You should input 2 numbers, I will multiplying them \n"
read -p "first one" firstnu
read -p "second one" secnu

total=$((${firstnu}*${secnu}))
echo -e "\n The result of ${firstnu}*${secnu} is ${total}"
