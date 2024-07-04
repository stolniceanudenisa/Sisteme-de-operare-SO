#awk -F ":"
BEGIN{
 for (i=1; i< ARGC; i++)
 { if ( i % 2 == 0){
    command="tail -r ARGC[i] | awk '{for (j=NF; j>0; j--) print $j }' ARGC[i]";
    command |getline;
    }  
   else{ 
    command="awk '{for (j = 1; j<=NF; j++_ print $j}' ARGC[i]";
    command |getline 
 }
 } 
}