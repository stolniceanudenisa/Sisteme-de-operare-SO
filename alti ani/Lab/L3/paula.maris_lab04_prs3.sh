#!/bin/bash
cuv=$1
k=1
for i in $*
do
    if [ $k -gt 1 ]
    then
        cat $i | sed "1,31{/$cuv/d}"
    fi
	k=$((k+1))
done
