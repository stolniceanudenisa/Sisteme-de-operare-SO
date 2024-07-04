#!/bin/sh

# directorul cu fișierele de transport
dir=$1

# verificam daca exista doar un parametru
if [ $# -ne 1 ]; then
    echo "parametru invalid">&2
    exit 1
# verificam daca parametrul dat este un director
elif [ ! -d $dir ]; then
        echo "parametru invalid">&2
        exit 1
fi

# parcurgem fiecare fișier
for file in $dir/*; do
    # verificam daca fisierul este text
    if [ -f $file ]; then
        # verificăm dacă primul rând conține "IN"
        first_line=$(head -n 1 "$file")
        if [ "$first_line" = "IN" ]; then
        # afișăm numele fișierului
            echo "$(basename "$file")"
        fi
    fi
done | sort
