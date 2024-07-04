#!/bin/bash

if [ ! -f "$1" ]; then
	echo "parametru invalid" >&2
	exit 0
fi

awk -F ',' '{
  producer=$1
  producerCount[producer]++
  powerSum[producer]+=$3
  capacitySum[producer]+=$4
} END {
  for (producer in producerCount) {
    powerAvg=int(powerSum[producer] / producerCount[producer])
    capacityAvg=int(capacitySum[producer] / producerCount[producer])
    
    printf("%s,%d,%d,%d\n", producer, producerCount[producer], powerAvg, capacityAvg)
  }
}' $1 | sort
