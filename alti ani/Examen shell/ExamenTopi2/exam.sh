#!/bin/sh

if [ $# -ne 1 ]; then
    echo "parametru invalid\n">&2
    exit 1
fi

if [ ! -f $1 ]; then
    echo "parametru invalid\n">&2
    exit 1
fi

grep -vc '^[1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]$' $1

exit 0
