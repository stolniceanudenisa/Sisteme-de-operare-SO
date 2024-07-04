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

echo OUT > transport2.txt
echo "ciment,2" >> transport2.txt
echo "adeziv,1" >> transport2.txt
echo "faianta,2" >> transport2.txt

echo IN > transport3.txt
echo "ciment,20" >> transport3.txt

echo IN > transport4.txt
echo "adeziv,10" >> transport4.txt
echo "faianta,20" >> transport4.txt

echo OUT > transport5.txt
echo "adeziv,8" >> transport5.txt

echo OUT > transport6.txt
echo "faianta,15" >> transport6.txt


#cleanup
cd $PWD
