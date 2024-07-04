BEGIN {print "Inceput de procesare"}
/e/ {print NR "Linie care contine lit. e"}
NF>1 {print NR "Linie care contine mai multe cuvinte"}
END {print FILENAME}
