#!/bin/bash

#prepare
PWD=`pwd`
WORK_DIR=`dirname $0`
WORK_DIR=`readlink -f $WORK_DIR`
cd $WORK_DIR/execute

#create files

mkdir depozit
cd depozit
echo IN > transport1.txt
echo "ciment,12" >> transport1.txt
echo "adeziv,9" >> transport1.txt
echo "faianta,20" >> transport1.txt

#cleanup
cd $PWD
