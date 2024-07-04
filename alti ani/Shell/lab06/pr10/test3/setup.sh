#!/bin/bash

#prepare
PWD=`pwd`
WORK_DIR=`dirname $0`
WORK_DIR=`readlink -f $WORK_DIR`
cd $WORK_DIR/execute

#create dirs and 
mkdir depozit
cd depozit
touch depozit.csv
touch transport1.csv

echo "ciment,4">depozit.csv

echo "OUT">transport1.csv
echo "ciment,1">>transport1.csv


#cleanup
cd $PWD
