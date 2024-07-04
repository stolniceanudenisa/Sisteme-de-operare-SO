#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 300

char model_max[100];
char marca_max[100];
int cai_max;

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "parametru invalid");
        return 0;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file)) {
    	int fdp[2];
    	if (pipe(fdp) == -1) {
        	fprintf(stderr, "eroare la pipe()");
        	return 1;
    	}
    	pid_t pid = fork();
    	if(pid < 0) { // eroare
    		fprintf(stderr, "eroare la fork()");
    		return 1;
    	}
    	else if(pid == 0) { // copil
    		close(fdp[0]);
    		char *marca = strtok(line, ",");
        	char *model = strtok(NULL, ",");
        	int cai = atoi(strtok(NULL, ","));
    		int n = strlen(marca);
        	write(fdp[1],&n,sizeof(int));
        	int m = strlen(model);
        	write(fdp[1],&m,sizeof(int));
        	write(fdp[1],marca,n*sizeof(char));
        	write(fdp[1],model,m*sizeof(char));
                write(fdp[1],&cai,sizeof(int));
        	close(fdp[1]);
        	exit(0);
        }

        else { // parinte
        	close(fdp[1]);
    		int n,m;
    		read(fdp[0],&n,sizeof(int));
    		read(fdp[0],&m,sizeof(int));
    		char *marca = (char*)malloc((n+1)*sizeof(char));
    		char *model = (char*)malloc((m+1)*sizeof(char));
    		read(fdp[0],marca,n);
    		marca[n] = '\0';
    		read(fdp[0],model,m);
    		model[m] = '\0';
    		int cai;
    		read(fdp[0],&cai,sizeof(int));
    		close(fdp[0]);
    		if(cai > cai_max) {
    			cai_max = cai;
    			strcpy(marca_max, marca);
    			strcpy(model_max, model);
    		}
        }
    }
    int status;
    while(wait(&status) > 0);
    printf("%s %s\n", marca_max, model_max);
    fclose(file);
    return 0;

}
