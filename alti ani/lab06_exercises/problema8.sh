#!/bin/bash
# Să se scrie un script bash care afişează, pentru fiecare fişier 
# dat ca argument, linia care apare de cele mai multe ori.

if [ $# -le 0 ]; then
	echo "parametru invalid" >&2
	exit 1
fi

for arg in $@; do
	if [ ! -f $arg ]; then
		echo "parametru invalid" >&2
		exit 1
	fi
	maxCount=0
	maxLine=""
	while read line1; do
		count=0
		while read line2; do
			if [ "$line1" == "$line2" ]; then
				count=$((count+1))
			fi
		done < $arg
		if [ $count -gt $maxCount ]; then
			maxCount=$count
			maxLine=$line1
		fi
	done < $arg
	echo "$maxLine"
done
