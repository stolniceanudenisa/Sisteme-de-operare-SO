#!/bin/bash
# Să se scrie un script bash care are ca argumente triplete formate 
# dintr-un nume de fisier, un cuvant si un numar k. Pentru fiecare 
# astfel de triplet, se vor afişa toate liniile fişierului care 
# contin cuvăntul respectiv exact de k ori.

if (( $# % 3 != 0 )); then
	echo "parametru invalid" >&2
	exit 1
fi

for ((i=1;i<=$#;i+=3)); do
	filename=${!i}
	if [ ! -f $filename ]; then
		echo "parametru invali" >&2
		exit 1
	fi
	eval cuvant=\${$((i+1))}
	eval k=\${$((i+2))}
	while read line; do
		count=0
		for word in $line; do
			if [ "$word" == "$cuvant" ]; then
				count=$((count+1))
			fi
		done
		if [ "$count" == "$k" ]; then
				echo $line
		fi
	done < $filename
	
done
