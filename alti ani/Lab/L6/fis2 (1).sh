#!/bin/bash
parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P ) 
mkdir dictionar
cd dictionar 

fisier="$parent_path/$1" 
for x in {a..z} 
do 
    c=$x
    b="${c^^}"
    touch "${c^^}"
    grep -oh "\<[$c$b][a-zA-Z0-9]*\>" $fisier > "${c^^}"
done

for x in {A..Z}
do
    sort -o $x $x
done
