#Să se scrie un script shell care tot citeşte nume de utilizatori de la intrarea standard (nu ca parametrii!).
#Pentru fiecare utilizator citit, el va afişa ultimele 3 conectări (logări) ale acestuia (în luna curentă), 
#iar dacă acesta nu s-a conectat deloc în luna curentă va afişa mesajul "userul x nu s-a conectat niciodată"


while true
do
	echo "dati numele de utilizator"
	read utilizator
	nrlog=$(last -n 3 $utilizator | grep Mar | wc -l)
	if [ "$utilizator" = "0"  ]
	then
		break
	elif [ $nrlog -eq "0" ]
	then
		echo "utilizatorul $utilizator nu s-a logat niciodata"
	else
		 last -n 3 $utilizator | grep Mar
	fi
done
