#!/bin/sh

if [ $# -ne 1 ]; then
    echo "parametru invalid\n">&2
    exit 1
fi

if [ ! -f $1 ]; then
    echo "parametru invalid\n">&2
    exit 1
fi

awk ' { puncte=0; puncte+=3*$1; puncte+=$3; print puncte } ' "$1"

exit 0
