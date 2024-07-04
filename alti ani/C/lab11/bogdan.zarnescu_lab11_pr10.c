#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define NUME_FIFO "fifo"

int main(int argc, char *argv[]) {
    char *dir = argv[1];
    
    if (mkfifo(NUME_FIFO, 0666) == -1) {
        perror("mkfifo");
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
            
            int pipefd_write = open(NUME_FIFO, O_WRONLY);
            if (pipefd_write == -1) {
                perror("open");
                exit(1);
            }
            
            f = fopen(file, "r");
            
            if (f == NULL) {
                exit(1);
            }
            
            int count = 0;
            
            while (fgets(line, 256, f) != NULL) {
                count = count + 1;
            }
            
            count = count - 1;
            
            // trimite rezultatul către procesul părinte prin pipe
            write(pipefd_write, &count, sizeof(count));
            
            fclose(f);
            close(pipefd_write);
            
            exit(0);
        } else {
            // părinte
            
            int pipefd_read = open(NUME_FIFO, O_RDONLY);
            if (pipefd_read == -1) {
                perror("open");
                exit(1);
            }
            
            int status;
            wait(&status);
            
            if (WIFEXITED(status) && WEXITSTATUS(status)) {
                fprintf(stderr, "parametru invalid\n");
                return 1;
            }
            
            int child_count=0;
            
            // primește rezultatul de la procesul copil prin pipe
            read(pipefd_read, &child_count, sizeof(child_count));
            
            close(pipefd_read);
            
            if (child_count) {
                printf("%d\n", child_count);
            }
        }
    }
    
    if (unlink(NUME_FIFO) == -1) {
        perror("unlink");
        exit(1);
    }
    
    return 0;
}
