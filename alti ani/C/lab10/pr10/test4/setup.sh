#!/bin/bash

#prepare
PWD=`pwd`
WORK_DIR=`dirname $0`
WORK_DIR=`readlink -f $WORK_DIR`
cd $WORK_DIR/execute

#create files

mkdir depozit
cd depozit

echo IN > transport3.txt
echo "ciment,20" >> transport3.txt

echo OUT > transport5.txt
echo "adeziv,8" >> transport5.txt



#cleanup
cd $PWD
