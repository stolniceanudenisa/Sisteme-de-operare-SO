#!/bin/bash
k=0
count=0
for i
do
	if [ $i != $1 ]
		then
			k=$(cat "$i" | grep -c "$1")
			if [ $k -gt 0 ]
				then
					echo "$i"
					count=$((count+1))
			fi
	fi
done
echo $count

