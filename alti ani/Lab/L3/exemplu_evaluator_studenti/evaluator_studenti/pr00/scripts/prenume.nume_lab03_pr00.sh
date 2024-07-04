#!/bin/sh

for filename in "$@"; do
    count=`wc -l $filename | cut -d ' ' -f 1`
    if [ $count -gt 2 ] ; then
        echo $filename
    fi
done

