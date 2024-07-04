#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    char *dir = argv[1];
    
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    
    for (int i = 2; i < argc; i++) {
        char file[256];
        strcpy(file, dir);
        strcat(file, "/");
        strcat(file, argv[i]);
        
        FILE* f;
        char line[256];
        
        int pid = fork();
        
        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // copil
            
            close(pipefd[0]);  // închide capătul de citire al pipe-ului în copil
            
            f = fopen(file, "r");
            
            if (f == NULL) {
                fprintf(stderr, "parametru invalid\n");
                exit(1);
            }
            
            int count = 0;
            
            while (fgets(line, 256, f) != NULL) {
                count = count + 1;
            }
            
            count = count - 1;
            
            // trimite rezultatul către procesul părinte prin pipe
            write(pipefd[1], &count, sizeof(count));
            close(pipefd[1]);
            
            fclose(f);
            exit(0);
        } else {
            // părinte
            
            close(pipefd[1]);  // închide capătul de scriere al pipe-ului în părinte
            
            int status;
            wait(&status);
            
            if (WIFEXITED(status) && WEXITSTATUS(status)) {
                return 1;
            }
            
            int child_count=0;
            
            // primește rezultatul de la procesul copil prin pipe
            read(pipefd[0], &child_count, sizeof(child_count));
            close(pipefd[0]);
            
            if (child_count) {
                printf("%d\n", child_count);
            }
        }
    }
    
    return 0;
}
