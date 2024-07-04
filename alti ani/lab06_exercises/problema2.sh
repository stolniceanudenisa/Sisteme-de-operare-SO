#!/bin/bash
# Să se scrie un script bash care primeşte ca argument un nume de
# director şi afişează primele 3 linii ale fiecărui fişier de tip
# text din acel director.

if [ ! -d $1 ]; then
	echo "parametru invalid"
	exit 1
fi

for file in $1/*; do
	extension="${file##*.}"
	if [ "$extension" == "txt" ]; then
		head -n 3 "$file"	
	fi
done

