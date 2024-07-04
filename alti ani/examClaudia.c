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
    
    int nrLinii = 0;
    int lung[10];
    char line[256];
    
    while (fgets(line, 256, f) != NULL) {
        nrLinii++;
        lung[nrLinii] = strlen(line);
    }
    
    fseek(f, 0, SEEK_SET);
    for (int i = 1; i <= nrLinii; i++) {
        fgets(line, 256, f);

        pid_t pid = fork();
        if (pid == -1) {
            perror("parametru invalid\n");
            fclose(f);
            exit(1);
        } else if (pid == 0) {
            //copil
            int count = 0;
            for (int j = 1; j < lung[i]; j++) {
                if (line[j] == ' ') {
                    count++;
                }
            }
            count++;
            printf("%d\n", count);
            fclose(f);
            exit(0);
        } else {
            //parinte
            int status;
            wait(&status);
        }
    }
    
    fclose(f);
    
    return 0;
}
