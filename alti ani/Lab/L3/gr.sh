#!/bin/bash
for i in $*
do
    cd $i
    a=$(ls | grep -v '\.txt$')
    for j in $a
    do
	echo $j
    done
    cd ..
done
