
#Să se afişeze pentru fiecare fişier: numele acestuia, şi numărul mediu de cuvinte per linie per fişier 
#(media numărului de cuvinte pentru liniile fişierului).
#Se va afişa şi media numărului de cuvinte pentru toate fişierele luate la 

for file in $*
do
        awk 'BEGIN{t=0}
        {t=t+NF}
        END{
        print FILENAME,":",t/NR 
        }' $file

c=$( wc -w "$file" | awk '{print $1}' )
total=$(( total += $c ))
contor=$(( contor += 1 ))

done
echo "Media cuvintelor per toate fisierele este: "
echo $total $contor 1k /p | dc 


