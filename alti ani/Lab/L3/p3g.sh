#!/bin/bash
for i in $*
do
	cd
	cd $i
	#grep -riL .
	a=$(ls | grep -v '\.txt$')
	for j in $a
	do
		echo $j
	done
done
