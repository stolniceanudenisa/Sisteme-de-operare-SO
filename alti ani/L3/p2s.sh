#!/bin/bash
for i
do
if [ $i != $1 ]
	then
		cat $i | sed "/$1/d"
fi
done
