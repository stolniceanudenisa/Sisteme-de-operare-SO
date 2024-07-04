#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
int main()
{
	int p[2],p2[2]; 
	int f,a,b,suma;
	if(pipe(p)<0)
	{
		perror("ERR creere pipe --1-- !!!");
		exit(1);
	}
	if(pipe(p2)<0)
	{
				
		perror("ERR creere pipe --2-- !!!");
		exit(5);
	}
	f=fork();
	if(f<0)
	{	
		perror("ERR fork !!!");
		exit(2);
	}
	if(f==0)//suntem in fiu
	{	
		close(p[1]);
		if(read(p[0],&a,sizeof(int))<sizeof(int) || read(p[0],&b,sizeof(int))<sizeof(int))
		{	
			perror("Err la citire din pipe");
			exit(4);
		}else{	
			close(p[0]);
			suma=a+b;
			close(p2[0]);
			if(write(p2[1],&suma,sizeof(int))<sizeof(int))
			{
				perror("Err la scriere in pipe --2--!!!");
				close(p2[1]);			
				exit(6);
			}
			
		}
	}else{
		close(p[0]);
		//parinte
		printf("Dati primul numar: ");
		scanf("%d",&a);
		printf("Dati cel de-al doilea numar: ");
		scanf("%d",&b);
		if(write(p[1],&a,sizeof(int))<sizeof(int) || write(p[1],&b,sizeof(int))<sizeof(int))
		{
			perror("Err la scriere in pipe --1--!!!");
			close(p[1]);			
			exit(3);
		}
		close(p2[1]);
		if(read(p2[0],&suma,sizeof(int))<sizeof(int))
		{	
			perror("Err la citire din pipe --2--");
			close(p2[0]);
			exit(7);
		}else{
			printf("Suma numerelor %d+%d este: %d\n",a,b,suma);
			close(p2[0]);
			exit(0);
		}

	}
	
	return 0;
}
