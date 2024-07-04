#!/bin/sh

dir=$1
fis=$2
old=$3
new=$4

sed -i -r "s/$old/$new/g" "$dir/$fis"
