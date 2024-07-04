#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("parametru invalid\n");
        return 1;
    }
    
    int suma = 0;
    
    for (int i = 1; i <= argc; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("parametru invalid\n");
            exit(1);
        } else if (pid == 0) {
            //copil
            int ok = 0;
            if (!isdigit(argv[i][0]) && argv[i][0] != '-') {
                ok = 1;
            }
            for (int j = 1; j < strlen(argv[i]); j++) {
                if (!isdigit(argv[i][j])) {
                    ok = 1;
                }
            }
            if (ok == 1) {
                exit(1);
            } else {
                exit(2);
            }
        } else {
            //parinte
            int status;
            wait(&status);
            if (WIFEXITED(status)) {
                if (WEXITSTATUS(status) == 1) {
                    perror("parametru invalid\n");
                    return 1;
                } else if (WEXITSTATUS(status) == 2) {
                    int nr = atoi(argv[i]);
                    suma += nr;
                }
            }
        }
    }
    
    printf("%d\n", suma);
    return 0;
}
