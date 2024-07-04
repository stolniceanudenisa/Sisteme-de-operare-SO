#!/bin/bash

CURRENT_DIRECTORY=`pwd`
WORK_DIR=`dirname $0`
WORK_DIR=`readlink -f $WORK_DIR`

cd $WORK_DIR

#defines
output="output.csv"
output_ok="output.ok"
rm $output 2>/dev/null
cp ./execute/depozit/depozit.csv $output
cat $output | sort > tmp1
cat $output_ok | sort > tmp2


cmp tmp1 tmp2>/dev/null
status=`echo $?`
rm tmp1 tmp2


cd $CURRENT_DIRECTORY
exit $status
