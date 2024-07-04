#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    char file[256];
    strcpy(file, argv[1]);
    
    FILE* f;
    
    f = fopen(file, "r");
    if (f == NULL) {
        fprintf(stderr, "parametru invalid\n");
        return 1;
    }
    
    int baieti = 0;
    int fete = 0;
    char line[256];
    
    int nrLinii = 0;
    
    while (fgets(line, 256, f) != NULL) {
        nrLinii++;
    }
    
    fseek(f, 0, SEEK_SET);
    
    for (int j = 1; j <= nrLinii; j++) {
        fgets(line, 256, f);
        pid_t pid = fork();
        if (pid == -1) {
            fprintf(stderr, "Fork error\n");
            exit(1);
        } else if (pid == 0) {
            int ok = 0;
            if (strlen(line) != 14) {                ok = 1;
            } else if (line[0] == '0') {
                ok = 1;
            } else {
                for (int i = 1; i < strlen(line) - 1; i++) {
                    if (line[i] < '0' || line[i] > '9' ) {
                        ok = 1;
                    }
                }
            }
            if (ok == 1) {
                exit(1);
            } else {
                int firstDigit = line[0] - '0';
                if (firstDigit % 2 == 0) {
                    exit(3);
                } else {
                    exit(4);
                }
            }
        } else {
            int status;
            wait(&status);

            if (WIFEXITED(status)) {
                if (WEXITSTATUS(status) == 3) {
                    fete += 1;
                } else if (WEXITSTATUS(status) == 4) {
                    baieti += 1;
                }
            }
        }
    }
    fclose(f);
    printf("fete:%d baieti:%d\n", fete, baieti);
    return 0;
}
