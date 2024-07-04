//Sa se numere cuvintele fiecarei linii dintr-un fisier. Nu se vor face presupuneri referitoare la dimensiunea maxima a unei linii.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char* argv[] ){
	FILE *f;
	int linecount;
	linecount=1;
	char *ch;
	int s=0;
	f=fopen(argv[1],"r");
if(f==NULL){
		printf("Fisierul nu exista!\n");
		exit(1);
		}
char* linie=NULL;
size_t n=0;
	while (getline(&linie,&n,f) != -1 ) {
		printf("Line: %d \n", linecount);
		ch=strtok(linie, " ");
		//while(ch=strtok(linie," ")) 
				 while (ch!=NULL){
				      	//printf("%s\n", ch);
					ch = strtok(NULL," ");
					s++;
 				}
		    printf("Nrwords: %d \n", s);
			printf("\n");
		    s=0;
			++linecount;
		}

fclose(f);
return 0;
}
