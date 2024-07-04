#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("parametru invalid\n");
        return 1;
    }
    
    FILE* f;
    f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("parametru invalid\n");
        return 1;
    }
    
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("parametru invalid\n");
        return 1;
    }
    
    char line[256];
    int nrLinii = 0;
    int lung[10];
    while (fgets(line, 256, f) != NULL) {
        nrLinii++;
        lung[nrLinii] = strlen(line);
    }
    
    fseek(f, 0, SEEK_SET);
    
    for (int i = 1; i <= nrLinii; i++) {
        fgets(line, 256, f);
        
        pid_t pid = fork();
        
        if (pid == -1) {
            perror("parametru invalid\n");
            exit(1);
        } else if (pid == 0) {
            //copil
            
            int puncte = 0;
            char* sep = " ";
            char* token = strtok(line, sep);
            
            int nr = atoi(token);
            puncte += 3*nr;
            
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            nr = atoi(token);
            puncte += nr;
            
            printf("%d\n", puncte);
            
            fclose(f);
            exit(0);
        } else {
            //parinte
            
            int status;
            wait(&status);
        }
    }
    
    fclose(f);
    
    return 0;
}
