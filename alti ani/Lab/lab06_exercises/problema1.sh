#!/bin/bash
#  Să se scrie un script bash care primeşte ca argument un număr
# natural N şi generează N fişiere de tip text, astfel:
# numele fişierelor vor fi de forma: file_X.txt, unde X = {1, 2, ..., N}
# fiecare fişier generat va conţine doar liniile de la X la X + 5 ale fişierului passwd.fake

if [ "$#" -le 0 ]; then
	echo "parametru invalid" <&2
	exit 1
fi

if [ "$1" -le 0 ]; then
	echo "parametru invalid" <&2
	exit 1
fi

for ((i=1;i<=$1;i++)); do
	touch "file_$i.txt"
	sed -n "$i,$((i+5))p" passwd.fake > "file_$i.txt"
done

