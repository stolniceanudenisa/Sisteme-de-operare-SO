#!/bin/bash

#prepare
PWD=`pwd`
WORK_DIR=`dirname $0`
WORK_DIR=`readlink -f $WORK_DIR`
cd $WORK_DIR/execute

#create dirs and 
mkdir dir1

cd dir1
echo "#include <stdio.h"> main.c
echo "#define P(x) (x)*(x)">> main.c
echo "int main(){ return 0; }">> main.c

echo "#include <stdio.h"> fis1.c
echo "#define P(x) (x)*(x)"> fis2.c
echo "int main(){ return 0; }">> fis3.c

echo "#include <stdio.h"> fis4.c
echo "#define HIT_POINT_CENTER 10">> fis4.c
echo "#define HIT_POINT 5">> fis4.c
echo "#define HIT_NO_POINT 0">> fis4.c
echo "int main(){ return 0; }">> fis4.c

cd ..

#cleanup
cd $PWD
