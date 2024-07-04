#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int suma = 0;
//    int pipefd[2];
//    if (pipe(pipefd) == -1) {
//        perror("pipe");
//        return 1;
//    }
    for (int i = 1; i <= argc; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork\n");
            exit(1);
        } else if (pid == 0) {
            //copil
//            close(pipefd[0]);
            
            int ok = 0;
            for(int j = 0; j < strlen(argv[i]); j++) {
                if (!isdigit(argv[i][j]) && argv[i][j] != '-') {
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
