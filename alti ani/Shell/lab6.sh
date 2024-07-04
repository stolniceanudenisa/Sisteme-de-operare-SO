
#Se dă un fişier text. Să se creeze un director care să conţină 10 de fişiere dicţionar, astfel:
#primul fişier conţine, ordonate alfabetic, câte unul pe linie, toate cuvintele din fişierul text
#care încep cu cifra '0', al doilea cu cifra '1' s.a.m.d.

#!/bin/bash
file=$1
directory=$2
mkdir $directory
cat $file | while read line;do
	cd $directory
	for i in {0..9};do
		var=${line:0:1}
		if [ "$var" = "$i" ]
			then
				if [ -e $i ]
				then 
				    echo "$line" >> "$i"
                                else
				    echo "$line" > "$i"
				fi
		fi
	done 
cd ..
done

cd $directory
echo ~~~~~~ "$directory" ~~~~~~
for i in {0..9};do
	echo Fisierul dictionar "$i" :
	cat "$i"
done



