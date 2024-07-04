#!/bin/bash
echo "Comenzi grep"

echo -e "\n\e[01;31mLiniile care incep cu 'a':\e[00;36m grep '^a' propozitii.txt\e[00;00m"
grep '^a' propozitii.txt

echo -e "\n\e[01;31mLiniile care incep cu 'a' si se termina cu 'e':\e[00;36m grep '^a' propozitii.txt\e[00;00m"
grep '^a.*e$' propozitii.txt

echo -e "\n\e[01;31mLiniile care contin 'n' si apoi 'i':\e[00;36m grep '^.*n.*i.*$' propozitii.txt\e[00;00m"
grep '^.*n.*i.*$' propozitii.txt

echo -e "\n\e[01;31mLiniile care contin 'n' si se termina cu 'e':\e[00;36m grep '^.*n.*e$' propozitii.txt\e[00;00m"
grep '^.*n.*e$' propozitii.txt

echo -e "\n\e[01;31mNumarul liniilor care contin 'n' si se termina cu 'e':\e[00;36m grep -c '^.*n.*e$' propozitii.txt\e[00;00m"
grep -c '^.*n.*e$' propozitii.txt

echo -e "\n\e[01;31mPattern-uri din fisier:\e[00;36m grep -f expresii.grep propozitii.txt\e[00;00m"
grep -f expresii.grep propozitii.txt
