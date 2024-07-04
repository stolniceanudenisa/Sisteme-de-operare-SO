//Fie un fişier ce conţine N numere întregi. 
//Folosind două tipuri de procese (unul pentru determinarea minimului şi celălalt pentru determinarea
//maximului valorilor dintr-un şir de numere), să se scrie un program care determină cel de-al k-lea 
//element în ordine crescătoare a unui şir de numere întregi, fără a ordona şirul.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

int main(){
FILE *f;
f=fopen("sirnr","r");
int sir[100];
int min,max;
int mi,ma;
int i=0,j,n,c,l;
int a,aux,k;
printf("Dati n=");
scanf("%d",&n);
for(i=1;i<=n;i++)
	fscanf(f,"%d",&sir[i]);
i=0;

for(i=1;i<=n;i++)
	printf("%d ",sir[i] );

printf("\n");

for(i=1;i<=n/2;i++)
{       mi=30000;
	ma=-30000;
	min=fork();
	if (min<0)
		printf("eroare la fork\n");
	if (min==0)
	{
	  for(c=i;c<=n-i+1;c++){
		if (sir[c]<mi){
		     mi=sir[c];
		     a=c;}
		}
	aux=sir[i];
	sir[i]=mi;
	sir[a]=aux;
	

	max=fork();
	if (max<0)
		printf("eroare la fork\n");
	if (max==0)
       {
           for(c=i;c<=n-i+1;c++){
                if (sir[c]>ma){
                        ma=sir[c];
			a=c;}
            }
	aux=sir[n-i+1];
	sir[n-i+1]=ma;
	sir[a]=aux;

       }

        if(max>0)
        {wait(0);
	exit(1);
        }



	}
	if (min>0)
	{ wait(0);
	exit(1);
	}
}

i=1;
for (i=1;i<=n;i++){
	printf("elem sirluilui %d \n", sir[i]); 
}


printf("Dati elementul dorit k= \n");
scanf("%d",&k);
printf("Elementul k in sir este %d \n:",sir[k]);

}




























