#include <stdio.h>
#include <stdlib.h>

FILE * f = fopen("fisier.txt","r");
char linie[255];
int i,suma;
int main ()
{
    if(f == NULL) perror("Eroare la deschiderea fisierului");
    else {
     if (fgets (linie, f)!=NULL){
         suma=0;
         for(i=0;i<strlen(f);i++)
             if(linie[i]>='0' && linie[i]<='9')
                 suma=suma+1;
         printf("suma este",suma);
         }
        fclose(f);
        }

}
