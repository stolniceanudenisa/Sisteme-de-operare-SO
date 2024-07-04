#!/bin/sh

dir=$1

# verificam daca primul parametru dat este un director
if [ ! -d $dir ]; then
        exit 1
fi

# verificam tot ce este in director
for file in "$dir"/*; do
    # verificam sa fie fisier
    if [ -f "$file" ]; then
        # salvam suma produselor din fisier
        total=$(awk -F ',' 'NR>1 {sum += $2} END {print sum}' "$file")
        # afisam numele fisierului + suma totala
        echo "$(basename "$file") $total"
    fi
done | sort
