#include <stdio.h>

int main()
{
FILE* file=fopen("fisier.txt", "r");
char linie[256];
int i,suma;

while (fgets(linie,"\n" , file))
{
//    printf("%s",linie);
      suma = 0;
      printf("sunt pe linia");
      printf("%i",i);

      for( i=0; i< sizeof(linie); i=i+1)
      {
   //   printf("sunt pe linia");
  //    printf("%i",i);
          if ((linie[i] > 0)||(linie[i] <= 9)){
             // if (linie[i] < 9){
                  suma = suma + 1;
             // }    
          }
      }
      printf("%i",suma);  
}

fclose(file);
return 0;
}