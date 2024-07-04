#!/bin/sh

dir=$1
fis=$2
old=$3
new=$4

sed -i -r "s/$old/$new/g" "$dir/$fis"




if grep -q "^$product," "$dir/depozit.csv"; then
    quantityInFile=$(grep "^$product," "$dir/depozit.csv" | cut -d ',' -f2)
    new=$((quantityInFile + quantity))
    sed -i -r "s/$product,$quantityInFile/$product,$new/" "$dir/depozit.csv"
else
    echo "$product,$quantity" >> "$dir/depozit.csv"
fi
