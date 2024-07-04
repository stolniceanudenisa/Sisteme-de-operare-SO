#Să se afişeze conţinutul tuturor fişierelor text din directorul dat ca parametru linia de comandă şi din subdirectoarele lui.GREP

director=$1
cd $director
for fis in `find -type f`
do
	if file $fis | grep -q "ASCII text";
	then
		cat $fis
	fi
done

