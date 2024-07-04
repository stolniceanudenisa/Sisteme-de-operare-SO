#!/bin/sh

if [ $# -ne 1 ]; then
    echo "parametru invalid\n">&2
    exit 1
fi

if [ ! -f $1 ]; then
    echo "parametru invalid\n">&2
    exit 1
fi

sed -i -r  's/un/1/g; s/doi/2/g; s/trei/3/g' $1

exit 0
