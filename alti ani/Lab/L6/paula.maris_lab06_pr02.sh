#!/bin/bash

fis=$1

if [ -d dictionar ]
then
    rm -r dictionar
fi

mkdir dictionar

for i in {A..Z}
do
    touch dictionar/$i
done

for cuv in $(cat $fis | sort )
do
    first=${cuv::1}
    if [[ $first == [[:alpha:]] ]]
    then
		lit=${first^}
        echo "$cuv" >> dictionar/$lit
    fi
done

for i in {A..Z}
do
    sort -o dictionar/$i dictionar/$i
done
