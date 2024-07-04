#!/bin/sh

suma=0

for nr in "$@"; do
    if [ "$nr" -eq "$nr" ]; then
        suma=$((suma + nr))
    else
        echo "parametru invalid">&2
        exit 1
    fi
done
echo "$suma"
exit 0
