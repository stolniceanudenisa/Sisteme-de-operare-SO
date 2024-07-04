# Să se scrie un script shell care să afișeze liniile dintr-un
# fișier care conțin cuvinte având între 5 și 7 vocale. Fișierul
# va fi furnizat ca parametru în linia de comandă. Cuvintele
# sunt despărțite prin spațiu și pot conține cifre și caractere
# speciale.

#!/bin/bash

if [ ! -f $1 ]; then
	echo "parametru invalid" >&2
	exit 1
fi

while read line;do
	for word in $line; do
		nrVocale=0
		lungime=${#word}
		for ((i=0;i<$lungime;i++)); do
			litera=${word:$i:1}
			if [[ $litera == "a" || $litera == "e" || $litera == "i" || $litera == "o" || $litera == "u" || $litera == "A" || $litera == "E" || $litera == "I" || $litera == "O" || $litera == "U" ]]; then
				nrVocale=$((nrVocale+1))
			fi
		done
		if [[ $nrVocale -ge 5 && $nrVocale -le 7 ]]; then
			echo $word
		fi
	done
done < "$1"
