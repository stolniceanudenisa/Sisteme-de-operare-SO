#CERINTA: Se da un fisier text. Sa se creeze un director care
#sa contina 26 de fisiere, astfel: primul fisier contine,ordonate
#alfabetic, cate unul pe linie, toate cuvintele din fisierul
#text care incep cu litera A, al doilea cu litera B, s.a

for cuvant in $(cat cuvinte.txt | sort -n cuvinte.txt) 
do
#	echo "$cuvant"
	for i in {a..z}
	do
	case "$cuvant" in
	$i*)
		echo "$cuvant" >> $i.txt
		echo "am gasit un cuvant care incepe cu $i"
		;; 
	esac
	done



#	case "$cuvant" in
#	a*)
#		echo "am gasit un cuvant cu a"
#		echo "$cuvant" >> A.txt
#		;;
#		
#	b*)
#		echo "$cuvant" >> B.txt	
#		echo "am gasit un cuvant cu b"
#		;;
#	esac
done 
