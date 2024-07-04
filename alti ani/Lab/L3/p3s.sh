#!/bin/bash
CUVANT=$1
shift
for i in $*
do
	cat $i | sed "1,31{/$CUVANT/d;}"
done
