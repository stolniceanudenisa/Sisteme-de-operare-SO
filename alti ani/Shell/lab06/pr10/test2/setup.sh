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
echo "adeziv,0">>depozit.csv

echo "IN">transport1.csv
echo "ciment,5">>transport1.csv
echo "adeziv,1">>transport1.csv


#cleanup
cd $PWD
