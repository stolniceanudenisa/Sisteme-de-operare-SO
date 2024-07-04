#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char* argv[]) {
    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "parametru invalid\n");
        return 1;
    }
    
    int nr_films = 0;
    int nr_series = 0;

    char line[512];
    while (fgets(line, sizeof(line), f) != NULL) {
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Error in waitpid\n");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            char type[10];
            char nume[20];
            int durata;
            int an;
            char tip[20];
            sscanf(line, "%[^;];%[^;];%d;%d;%[^;]", nume, type, &durata, &an, tip);
            if (strcmp(type, "film") == 0) {
                exit(EXIT_SUCCESS + 1);
            }
            else if (strcmp(type, "serial") == 0) {
                exit(EXIT_SUCCESS + 2);
            }
            else {
                exit(EXIT_FAILURE);
            }
            // Add the following line to exit the child process
            exit(EXIT_FAILURE);
        }
    }
    
    int status;
    pid_t child_pid;
    while ((child_pid = wait(&status)) > 0) {
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status == EXIT_SUCCESS + 1) {
                nr_films++;
            }
            else if (exit_status == EXIT_SUCCESS + 2) {
                nr_series++;
            }
        }
    }
    
    fclose(f);
    printf("%d\n", nr_films);
    printf("%d\n", nr_series);
    return 0;
}

