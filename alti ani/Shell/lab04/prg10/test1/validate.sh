#!/bin/bash

CURRENT_DIRECTORY=`pwd`
WORK_DIR=`dirname $0`
WORK_DIR=`readlink -f $WORK_DIR`

cd $WORK_DIR

#defines
output="output"
output_ok="output.ok"
input_param="input_param"

dir_name=`cat $input_param | cut -d ' ' -f 1`
file_name=`cat $input_param | cut -d ' ' -f 2`
file_path="$dir_name/$file_name"


cd ./execute/
cat "$file_path" >$WORK_DIR/$output
cd $WORK_DIR

# check diff between "output" and "output.ok"
cmp $output $output_ok>/dev/null
status=`echo $?`
#rm $output_tree


cd $CURRENT_DIRECTORY
exit $status
