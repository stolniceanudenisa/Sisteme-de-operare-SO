# 1. Sa se scrie un script shell care primeste ca si argumente un cuvant si oricate fisiere. 
# Sa se afiseze pentru cate dintre fisierele care contin cuvantul dat utilizatorul are drept de executie.

if [ $# -lt 1 ]; then
    echo "ERROR: Not enough arguments!"
    exit
fi

STRING=$1
# FOUND_STR=0
FOUND_EXE=0

shift

for FILE in $*; do
    if [ -e $FILE ]; then
        if [ $(grep -c "$STRING" "$FILE") -gt 0 ]; then
#            FOUND_STR=$((FOUND_STR+1))
            if [ $(ls -l "$FILE" | grep -c ".........x") -gt 0 ]; then
                FOUND_EXE=$((FOUND_EXE+1))
            fi
        fi
    else
        echo "WARNING: '$FILE' is not a valid file! Skipping this one..."
    fi
done

# echo "$FOUND_STR of the given files contain the string '$STRING'"
echo "$FOUND_EXE of the given files contain the string '$STRING' AND  are executable by '$USER'"

