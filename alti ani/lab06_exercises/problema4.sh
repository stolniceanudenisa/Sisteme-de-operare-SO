#!/bin/bash
# Să se scrie un script bash care afișează numele fișierelor dintr-
# un director dat ca parametru care conțin numere de peste 5 cifre.

if [ ! -d $1 ]; then
	echo "parametru invalid" >&2
	exit 1
fi

for file in $1/*; do
	if [ ! -f $file ]; then
		echo "parametru invalid" >&2
		exit 1
	fi
	filename=$(basename "$file")
	echo "$filename" | grep -E "[1-9][0-9]{5,}"
done
