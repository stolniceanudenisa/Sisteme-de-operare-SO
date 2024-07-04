//Sa se numere toate cifrele fiecarei linii dintr-un fisier.


#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE *file;
    char *line =NULL;
    size_t len = 0;
    ssize_t read;
    
    file= fopen("fisier.txt","r");
    if (file == NULL)
        exit(EXIT_FAILURE);
        
    while ((read = getline (&line, &len, file)) != -1)
    {
        int suma=0;
        printf("Am citit linia de lungime  %zu :\n", read);
        printf("%s",line);
        for(int i=0; i< read ; i=i+1){
              if (isdigit(line[i]))
               suma= suma+1;
        }
        printf("Numarul de cifre din aceasta linie: \n");
        printf("%i\n",suma);
    }
    
free(line);
fclose(file);
//exit(EXIT_SUCCES);
}