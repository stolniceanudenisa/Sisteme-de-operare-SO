#!/bin/bash

for fis in $*
do
    awk '{voc+=gsub(/[aeiouAEIOU]/,"")} {cons+=gsub(/[bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ]/,"")}
    END{print FILENAME, voc, cons}' $fis
done

