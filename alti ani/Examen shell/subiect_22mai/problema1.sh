#!/bin/bash

if [ ! -f $1 ]; then
	echo "parametru invalid" >&2
	exit 1
fi

sum=0
k=0
while read line; do
	for number in $line; do
		sum=$((sum+$number))
		k=$((k+1))
	done
done < $1
let medie=$sum/$k
echo $medie
