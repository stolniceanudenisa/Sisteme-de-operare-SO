#!/bin/bash

if [ ! -f $1 ]; then
	echo "parametru invalid" >&2
	exit 1
fi

noCorecte=$(grep -Eo "^[1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]$" "$1" | wc -l)
noTotale=$(wc -l < "$1")
let noGresite=$noTotale-$noCorecte
echo $noGresite

