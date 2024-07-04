#!/bin/bash

if [ ! -f "$1" ]; then
	echo "parametru invalid" >&2
	exit 0
fi

if [[ ! "$4" =~ ^[0-9]+$ ]]; then
	echo "parametru invalid" >&2
	exit 0
fi

sed -i "/^$2,$3,/s/,[0-9]\+/,${4}/" "$1"
