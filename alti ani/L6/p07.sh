#!/bin/bash

read numar
if [ $numar -le 1 ]
then
    echo "not prime"
else
    ok=0
    i=2
    n=$(( numar/2 ))
    while [ $i -le $n ]
    do
        nr=$(( numar%i ))
        if [ $nr -eq 0 ]; then
            ok=1
        fi
        i=$(( i+1 ))
    done
    if [ $ok -eq 1 ]; then
        echo "not prime"
    else
        echo "prime"
    fi
fi
