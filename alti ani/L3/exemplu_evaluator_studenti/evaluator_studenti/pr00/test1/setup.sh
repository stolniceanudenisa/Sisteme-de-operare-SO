#!/bin/bash

#prepare
PWD=`pwd`
WORK_DIR=`dirname $0`
WORK_DIR=`realpath $WORK_DIR`
cd $WORK_DIR/execute

#create files
echo "abcdef" > fis1
echo "ghijklmn" >> fis1
echo "opqrstuv" >> fis1

echo "qwertyuiop" > fis2
echo "asdfghjkl" >> fis2
echo "zxcvbnnm" >> fis2

echo "doar o linie" > fis3

echo "doar doua" > fis4
echo "linii" >> fi4


#cleanup
cd $PWD
