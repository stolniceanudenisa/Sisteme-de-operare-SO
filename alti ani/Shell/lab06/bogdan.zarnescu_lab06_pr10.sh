#!/bin/sh

# verificam ca exista cel putin 2 parametri
if [ $# -lt 2 ]; then
  exit 1
fi

dir=$1

# verificam daca primul parametru dat este un director
if [ ! -d "$dir" ]; then
    exit 1
fi

# verificam daca exista depozit.csv se afla in directorul dat
if [ ! -f "$dir/depozit.csv" ]; then
    exit 1
fi

# parcurgem toti parametri dati
for file in "${@:2}"; do
    # verificam daca parametrul este fisier
    if [ ! -f "$dir/$file" ]; then
        exit 1
    fi
    
    tip=$(head -n 1 "$dir/$file")
    # verificam tipul fisierului de transport
    if [ "$tip" != "IN" ] && [ "$tip" != "OUT" ]; then
        exit 1
    fi

    # parcurgem fisierul linie cu linie
    while read -r line; do
        # verificam ca linia respectiva sa nu fie "IN" sau "OUT"
        if [ "$line" != "IN" ] && [ "$line" != "OUT" ]; then
            product=$(echo "$line" | cut -d ',' -f 1)
            quantity=$(echo "$line" | cut -d ',' -f 2)
            
            if [ "$tip" = "IN" ]; then
                if grep -q "^$product," "$dir/depozit.csv"; then
                    quantityInFile=$(grep "^$product," "$dir/depozit.csv" | cut -d ','  -f2)
                    new=$((quantityInFile + quantity))
                    sed -i -r "s/$product,$quantityInFile/$product,$new/"   "$dir/depozit.csv"
                else
                echo "$product,$quantity" >> "$dir/depozit.csv"
                fi
            else
                quantityInFile=$(grep "^$product," "$dir/depozit.csv" | cut -d ',' -f2)
                new=$((quantityInFile - quantity))
        
                # Verificam daca exista suficient stoc in depozit
                if [ "$new" -lt 0 ]; then
                    exit 1
                fi
                sed -i -r "s/$product,$quantityInFile/$product,$new/" "$dir/depozit.csv"
            fi
        fi
    done < "$dir/$file" | tail -n +2
done
