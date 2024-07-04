#!/bin/bash
# Să se scrie un script bash care calculează numărul mediu de linii 
# ale fișierelor de tip text dintr-un director dat ca parametru.

if [ ! -d $1 ]; then
	echo "parametru invalid" >&2
	exit 1
fi

sum=0
count=0
for file in $1/*; do
	extension="${file##*.}"
	if [ "$extension" == "txt" ]; then
		linii=$(wc -l < "$file")
		sum=$((sum+linii))
		count=$((count+1))
	fi
done
let medie=$sum/$count
echo $medie
