#!/bin/bash
#Program:
#	Users input a scale number to calculate pi number
#History:
#2022/05/30	zcj	release 1
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH
echo "This program will calculate pi value \n"
echo "You should input a float number to calculate pi value"
read -p "The scale number (10~10000) is " checking
num=${checking:-"10"} #检测是否有输入数值
echo "Starting calculate pi calue, Be patient"
time echo "scale=${num};4*a(1)" |bc -lq

