#Pentru o lista de servere date ca parametri in linia de comanda
#se cere sa se afiseze daca sunt accesibile sau nu
urls=$@
COUNT=1
for url in $urls
do
	value=$(ping -c $COUNT $url | grep 'received' | awk -F',' '{ print $2 }' | awk '{ print $1 }')
	if [[ $value -eq "0" ]]; then 
		echo "$url IS DOWN"
	else echo "$url EXIST"
	fi
	
	#if ping -c 3 $url 
	#then
	#	echo "$url EXIST"
	#else
	#	echo "$url NOT EXIST"
	#fi
done