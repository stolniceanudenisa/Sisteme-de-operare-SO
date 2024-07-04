#Problema cu owner
first="$1"
list_of_users=$(cut -d: -f1 /etc/passwd)
current_user="$USER"
#echo $current_user
#l=$(grep "$1" /etc/passwd)
#echo $list_of_users
for user in $list_of_users
do 
	if [ "$user" == "$first" ];
	then
		sudo chown -R $current_user /home/ioana
	else echo " "
	fi  
done