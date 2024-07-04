#!/bin/sh

if [ $# -ne 1 ]; then
    echo "parametru invalid\n">&2
    exit 1
fi

if [ ! -f $1 ]; then
    echo "parametru invalid\n">&2
    exit 1
fi

#awk '{
#    num_cuvinte = 0
#    for (i = 1; i <= length($0); i++) {
#        if (substr($0, i, 1) == " ") {
#            num_cuvinte++
#        }
#    }
#    num_cuvinte++  # Adaugă unul pentru ultimul cuvânt de pe linie
#    print num_cuvinte }' $1

awk ' {print NF} ' $1
