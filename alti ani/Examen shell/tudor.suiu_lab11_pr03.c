#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LINE_LENGTH 300
#define NUME_FIFO "lab11.fifo"

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
    	int status = mkfifo(NUME_FIFO,0666);
    	if(status == -1) {
    		fprintf(stderr, "eroare la mkfifo()");
    	}
    	pid_t pid = fork();
    	if(pid < 0) { // eroare
    		fprintf(stderr, "eroare la fork()");
    		return 1;
    	}
    	else if(pid == 0) { // copil
    		int fd = open(NUME_FIFO, O_WRONLY);
    		char *marca = strtok(line, ",");
        	char *model = strtok(NULL, ",");
        	int cai = atoi(strtok(NULL, ","));
    		int n = strlen(marca);
        	write(fd,&n,sizeof(int));
        	int m = strlen(model);
        	write(fd,&m,sizeof(int));
        	write(fd,marca,n*sizeof(char));
        	write(fd,model,m*sizeof(char));
                write(fd,&cai,sizeof(int));
                close(fd);
                fclose(file);
        	exit(0);
        }

        else { // parinte
        	int fd = open(NUME_FIFO, O_RDONLY);
    		int n,m;
    		read(fd,&n,sizeof(int));
    		read(fd,&m,sizeof(int));
    		char *marca = (char*)malloc((n+1)*sizeof(char));
    		char *model = (char*)malloc((m+1)*sizeof(char));
    		read(fd,marca,n);
    		marca[n] = '\0';
    		read(fd,model,m);
    		model[m] = '\0';
    		int cai;
    		read(fd,&cai,sizeof(int));
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
    unlink(NUME_FIFO);
    return 0;

}
