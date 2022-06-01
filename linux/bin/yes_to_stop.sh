
until [ "${yn}" == "yes" -o "${yn}" == "YES" ]
#while [ "${yn}" != "yes" -a "${yn}" != "YES" ]
do
	read -p "Please input yes/YES to stop program : " yn

done
echo "OK! You input the correct answer."
