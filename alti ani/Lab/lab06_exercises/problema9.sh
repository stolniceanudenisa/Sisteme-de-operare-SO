#!/bin/bash
# Să se scrie un script bash care va afişa toate numele de fişiere 
# dintr-un director dat ca parametru şi din subdirectoarele sale, 
# care au numele mai scurte de 8 caractere. Pentru acestea, dacă 
# sunt fişiere text, li se vor afişa primele 10 linii.

if [ ! -d $1 ]; then
	echo "parametru invalid" >&2
	exit 1
fi

for file in $1/*; do
	filename=$(basename $file)
	length=${#filename}
	extension="${file##*.}"
	if [ $length -le 8 ]; then
		echo $filename
		if [ "$extension" == "txt" ]; then
			head -n 10 "$file"
		fi
	fi
done
