#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

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
    
    int count = 0;
    char line[256];
    
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }
    
    int nrLinii = 0;
    int lung[10];
    
    while (fgets(line, 256, f) != NULL) {
        nrLinii++;
        lung[nrLinii] = strlen(line);
    }
    
    fseek(f, 0, SEEK_SET);
    
    for (int j = 1; j <= nrLinii; j++) {
        fgets(line, 256, f);
        
        pid_t pid = fork();

        if (pid == -1) {
            perror("parametru invalid\n");
            fclose(f);
            exit(1);
        } else if (pid == 0) {
            //copil
            int trimis = 0;
            for (int i = 0; i < lung[j]; i++) {
                if (isdigit(line[i])) {
                    trimis++;
                }
            }
            write(pipefd[1], &trimis, sizeof(int));
            fclose(f);
            exit(0);
        } else {
            //parinte
            int primit;
            int status;
            wait(&status);
            if (WIFEXITED(status)) {
                if (WEXITSTATUS(status) == 0) {
                    read(pipefd[0], &primit, sizeof(int));
                    count += primit;
                }
            }
        }
    }
    
    close(pipefd[0]);
    close(pipefd[1]);
    
    fclose(f);
    
    printf("%d\n", count);
    
    return 0;
}
