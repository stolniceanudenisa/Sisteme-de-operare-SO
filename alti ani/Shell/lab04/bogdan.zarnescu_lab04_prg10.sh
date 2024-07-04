#!/bin/sh

# verificam daca exista doar un parametru
if [ $# -ne 2 ]; then
    echo "parametru invalid">&2
    exit 1
fi
    
# directorul cu fișierele de transport
dir=$1
fis=$2

# verificam daca primul parametru dat este un director
if [ ! -d $dir ]; then
        #echo "parametru invalid">&2
        exit 1
fi

# verificam daca al doilea parametru se afla in directorul dat ca prim parametru
if [ ! -f $dir/$fis ]; then
    echo "parametru invalid">&2
    exit 1
fi

# verificam formatul cerut
grep -E '^IN|OUT$|^([a-zA-Z]+( [a-zA-Z]+)*)\,[0-9]+$' -i -- "$dir/$fis" > tmpfile && mv tmpfile "$dir/$fis"
