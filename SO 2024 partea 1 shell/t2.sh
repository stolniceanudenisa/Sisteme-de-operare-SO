#Sa se adauge in fata fiecarei litere mici cuvantul indicat ca
#prim parametru. Fisierele tratate sunt ceilalti parametrii din
#linia de comanda.
first=$1
for file in "${@:2}"
do
sed -r 's/[a-z]/'$first' &/g' $file	
done