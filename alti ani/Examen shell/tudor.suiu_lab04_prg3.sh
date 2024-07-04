#!/bin/bash

if [ ! -f "$1" ]; then
	echo "parametru invalid" >&2
	exit 0
fi

if ! echo "$2" | grep -Eq '^[[:alpha:][:space:]]+$'; then
	echo "parametru invalid" >&2
	exit 0
fi

no_models=$(grep "^$2," "$1" | cut -d ',' -f 2 | sort | uniq | wc -l)

echo "$no_models"
