#!/bin/bash
for i in $*
do
    cd $i
    grep -r -l "\x00"
    cd ..
done
