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
touch transport2.csv
touch transport3.csv

echo "ciment,1">depozit.csv
echo "adeziv,2">>depozit.csv
echo "kit de rosturi,3">>depozit.csv
echo "tabla,4">>depozit.csv

echo "IN">transport1.csv
echo "ciment,1">>transport1.csv
echo "adeziv,1">>transport1.csv
echo "kit de rosturi,1">>transport1.csv

echo "OUT">transport2.csv
echo "tabla,4">>transport2.csv

echo "OUT">transport3.csv
echo "ciment,2">>transport3.csv
echo "adeziv,2">>transport3.csv
echo "kit de rosturi,2">>transport3.csv

echo "OUT">transport4.csv
echo "adeziv,1">>transport4.csv
echo "kit de rosturi,2">>transport4.csv


#cleanup
cd $PWD
