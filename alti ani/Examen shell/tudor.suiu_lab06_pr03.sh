#!/bin/bash

if [ ! -f "$1" ]; then
	echo "parametru invalid" >&2
	exit 0
fi

if [ ! -f "$2" ]; then
	echo "parametru invalid" >&2
	exit 0
fi

while read line; do
	marca=$(echo $line | cut -d, -f 1)
	model=$(echo $line | cut -d, -f 2)
	cai_putere=$(echo $line | cut -d, -f 3)
	capacitate_cilindrica=$(echo $line | cut -d, -f 4)
	dotari=$(echo $line | cut -d, -f 5)
	impozit=$(awk -F ',' -v cap="$capacitate_cilindrica" '{ if(cap >= $1 && cap <= $2) print int(cap/200*$3) }' $2)
	echo "$marca,$model,$cai_putere,$capacitate_cilindrica,$dotari,$impozit" >> tmp.txt
done < $1

mv tmp.txt $1
rm tmp.txt
