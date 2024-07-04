#!/bin/bash
# Să se scrie un script bash care afișează primele 5 linii și 
# ultimele 5 linii ale fișierelor de tip text din directorul curent. 
# Dacă un fișier are mai puțin de 10 linii, atunci va fi afişat în 
# întregime

for file in $PWD/*; do
	extension="${file##*.}"
	if [ "$extension" == "txt" ]; then
		if [ $(wc -l < "$file") -le 9 ]; then
			cat "$file"
		fi
		if [ $(wc -l < "$file") -ge 10 ]; then
			head -n 5 "$file"
			tail -n 5 "$file"
		fi
	fi
done
