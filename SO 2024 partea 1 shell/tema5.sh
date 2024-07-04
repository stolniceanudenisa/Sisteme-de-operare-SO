#Sa se afiseze continutul oricator fisiere dupa cum urmeaza
#primul fisier asa cum este, iar fisierul urmator cu cuvintele
#in ordine inversa serparate prin :)

for file in "${@:1}"
do
#	if [[ file  % 2 == '0']]
#	then
#	command=$(
	tail -r $file | awk '{for (i=NF;i>0;i--) print $i}' $file
#	fi
done
		