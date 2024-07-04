#!/bin/bash
# Să se scrie un script bash care pentru fiecare parametru din linia 
# de comandă:
# dacă e fișier, se vor afișa numele, numărul de caractere și de 
# linii din el (în această ordine)
# dacă e director, numele și câte fișiere conține (inclusiv în 
# subdirectoare).

if [ $# -le 0 ]; then 
	echo "parametru invalid" >&2
	exit 1
fi

for arg in "$@"; do
	if [ -f "$arg" ]; then
		filename=$(basename "$arg")
		noChars=$(wc -m < "$arg")
		noLines=$(wc -l < "$arg")
		echo "$filename" "$noChars" "$noLines"
	fi
	if [ -d "$arg" ]; then
		dirname=$(basename "$arg")
		noFiles=$(find "$arg" -type f | wc -l)
		echo $dirname $noFiles
	fi
done
