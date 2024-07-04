
#Să se ştearga cuvintele de pe poziţiile 2 şi 4 din fişierele indicate ca parametri. 
#Cuvintele conţin doar litere sau cifre şi sunt desparţite prin spaţiu.SED

for fis in $*
do
	sed 's/^\(\<[^ ]*\>\) \(\<[^ ]*\>\) \(\<[^ ]*\>\) \(\<[^ ]*\>\) \(.*\)/\1 \3 \5/' $fis
done
