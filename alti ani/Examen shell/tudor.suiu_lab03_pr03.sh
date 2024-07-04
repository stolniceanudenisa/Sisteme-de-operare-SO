#!/bin/bash

# [ ! -f parametru ] - verifica daca fisierul nu exista
# [ ! -d parametru ] - verifica daca directorul nu exista 
# >&2 trimite eroarea in stderr
if [ ! -f "$1" ]; then
	echo "parametru invalid" >&2
	exit 0
fi

# read line citeste din fisierul "done < $1"
while read line; do
	# cut -d  "separator", -f 4 (de ex cuv1,cuv2,cuv3,cuv4 => cuv4)
	capacitate_cilindrica=$(echo $line | cut -d, -f 4)
	# cut -d "separator", -f 3 (de ex cuv1,cuv2,cuv3,cuv4 => cuv4)
	cai_putere=$(echo $line | cut -d, -f 3)
	# let permite calculul si atribuirea valorii unei expresii matematice la o variabila
	let raport=$capacitate_cilindrica/$cai_putere
	# afisam rezultatul
	echo $raport
# < $1 arata din ce fisier se citeste (fisierul dat in parametrul 1)
done < $1
