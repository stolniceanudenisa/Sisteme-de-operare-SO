#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
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
    
    char line[256];
    int nrLinii = 0;
    while (fgets(line, 256, f) != NULL) {
        nrLinii++;
    }
    
    fseek(f, 0, SEEK_SET);
    
    int baieti = 0, fete = 0;
    
    for (int i = 1; i <= nrLinii; i++) {
        fgets(line, 256, f);
        pid_t pid = fork();
        if (pid == -1) {
            perror("parametru invalid\n");
            exit(1);
        } else if (pid == 0) {
            //copil
            int ok = 0;
            if (strlen(line) != 14) {
                ok = 1;
            } else if (line[0] == '0') {
                ok = 1;
            } else {
                printf("%s\n", line);
                for (int j = 0; j < strlen(line) - 1; j++) {
                    if (!isdigit(line[j])) {
                        ok = 1;
                        break;
                    }
                }
            }
            
            if (ok == 1) {
                exit(1);
            } else {
                int fs = line[0] - '0';
                if (fs % 2 == 0) {
                    exit(2);
                } else {
                    exit(3);
                }
            }
        } else {
            //parinte
            int status;
            wait(&status);
            if (WIFEXITED(status)) {
                if (WEXITSTATUS(status) == 2) {
                    fete++;
                } else if (WEXITSTATUS(status) == 3) {
                    baieti++;
                }
            }
        }
    }
    
    fclose(f);
    
    printf("%d %d\n", baieti, fete);
    
    return 0;
}
