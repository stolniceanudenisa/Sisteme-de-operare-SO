#!/bin/bash

max_sum=0
poz_max=0
i=0
for fis in $*
do
    cuv=0
    awk '{ cuv+=NF } 
    END { 
    if $cuv -gt $max_sum
    then
        poz_max=$i
        max_sum=$cuv
    fi
    }' $fis
    i=$((i+1)) 
done
echo $poz_max
echo $max_sum
#awk '{ cuv+=NF } END { print cuv/NR }' $*

