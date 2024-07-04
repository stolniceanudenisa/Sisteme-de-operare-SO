#include<stdio.h>
#include<stdlib.h>

int main( int argc, char* argv[])
{
	FILE *f;
	if(argc < 2){
		printf("Dati nume de fisier\n");
		exit(1);
	}
	f = fopen(argv[1],"r");
	if(f == NULL){
		printf("Fisierul nu exista!\n");
		exit(1);
	}
	char* linie = NULL;
	size_t n = 0;
	while (getline(&linie,&n,f) != -1)
		if (*linie != '\n')
		    printf(linie);
	free(linie);
	return 0;
}
