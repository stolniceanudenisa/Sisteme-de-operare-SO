#!/bin/bash

#prepare
PWD=`pwd`
WORK_DIR=`dirname $0`
WORK_DIR=`readlink -f $WORK_DIR`
cd $WORK_DIR/execute

#create dirs and 
echo "These example sentences are selected automatically from various online news sources to reflect current usage of the word proposition" > fis1

echo "cuv1 cuv1 cuv1 cuv1 cuv1 cuv1 cuv1 cuv1" > fis2
echo "123456789101112131415" >> fis2

echo "qwertyuiopasdfghjklzxcvbnm qwertyuiopasdfghjklzxcvbnm qwertyuiopasdfghjklzxcvbnm" > fis3
echo "firstword secondword firstword" >> fis3

echo "qwertyuiopasdfghjklzxcvbnm123123123" > fis4
echo "abc def qwe asd zxc vbn mlp opk wert wer" >> fis4

echo "nothing" >fis5
echo "something such as a plan or offer that is presented to a person or group of people to consider" >>fis5
echo "to do but not do " >>fis5

#cleanup
cd $PWD
