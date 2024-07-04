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

    int fd[2];
    if (pipe(fd) == -1) {
        fprintf(stderr, "Error creating pipe\n");
        return 1;
    }

    char line[512];
    while (fgets(line, sizeof(line), f) != NULL) {
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Error in waitpid\n");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            close(fd[0]);  // Close the read end of the pipe

            char type[10];
            char nume[20];
            int durata;
            int an;
            char tip[20];
            sscanf(line, "%[^;];%[^;];%d;%d;%[^;]", nume, type, &durata, &an, tip);
            if (strcmp(type, "film") == 0) {
                write(fd[1], "film", sizeof("film"));
                exit(EXIT_SUCCESS);
            }
            else if (strcmp(type, "serial") == 0) {
                write(fd[1], "serial", sizeof("serial"));
                exit(EXIT_SUCCESS);
            }
            else {
                write(fd[1], "other", sizeof("other"));
                exit(EXIT_FAILURE);
            }
        }
    }

    close(fd[1]);  // Close the write end of the pipe

    char buffer[10];
    while (read(fd[0], buffer, sizeof(buffer)) > 0) {
        if (strcmp(buffer, "film") == 0) {
            nr_films++;
        }
        else if (strcmp(buffer, "serial") == 0) {
            nr_series++;
        }
    }

    fclose(f);
    printf("%d\n", nr_films);
    printf("%d\n", nr_series);
    return 0;
}
