#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 300

char marca_max[100];
char model_max[100];
int cai_max = 0;

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "parametru invalid");
        return 0;
    }
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file)) {
    	pid_t pid = fork();
    	if(pid < 0) { // eroare
    		fprintf(stderr, "eroare la fork()");
    	}
    	else if(pid == 0) { // copil
       		char *marca = strtok(line, ",");
        	char *model = strtok(NULL, ",");
        	int cai = atoi(strtok(NULL, ","));
        	if (cai > cai_max) {
            		strcpy(marca_max, marca);
            		strcpy(model_max, model);
            		cai_max = cai;
        	}
        }
        else { // parinte
        	int status;
        	wait(&status);
        	exit(0);
        }
    }
    printf("%s %s\n", marca_max, model_max);

    fclose(file);
    return 0;
}
