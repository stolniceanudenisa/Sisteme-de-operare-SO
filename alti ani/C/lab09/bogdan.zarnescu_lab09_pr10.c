#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    char *dir = argv[1];
    
    for (int i = 2; i < argc; i++) {
        char file[256];
        strcpy(file, dir);
        strcat(file, "/");
        strcat(file, argv[i]);
        
        FILE* f;
        char line[256];
        
        int pid = fork();
        
        if (pid==0) {
            //copil
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
            
            fprintf(stdout, "%d\n", count);
            
            fclose(f);
            exit(0);
        }
        int status;
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status)) {
            return 1;
        }
    }
    return 0;
}

