#!/bin/bash
awk '
{	
	hashmap[FILENAME]=hashmap[FILENAME]+NF
}
END{
	name=" "
	size=0
	for (elem in hashmap)
	{
		if (hashmap[elem]>=size)
		{
			size=hashmap[elem]
			name=elem
		}
	}
	print(name, size)
	
}'  $@
