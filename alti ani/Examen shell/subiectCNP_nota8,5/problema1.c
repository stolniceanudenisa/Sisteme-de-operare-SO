#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define NUME_FIFO "pipe.fifo"

int main(int argc, char* argv[]) {
	FILE *file = fopen(argv[1], "r");
	if(file == NULL) {
		fprintf(stderr, "eroare la fopen()\n");
		return 1;	
	}
	int status = mkfifo(NUME_FIFO, 0666);
	if(status == -1) {
		fprintf(stderr, "eroare la mkfifo()\n");
		return 1;
	}
	char line[100];
	while(fgets(line, 100, file)) {
		pid_t pid = fork();
		if(pid < 0) { // eroare
			fprintf(stderr, "eroare la fork()\n");
			return 1;
		}
		else if(pid == 0) { // copil
			if(strlen(line) == 13 && line[0] != '0') {
				int fd = open(NUME_FIFO, O_WRONLY);
				int primaCifra = line[0] - '0';
				int boyOrGirl = primaCifra % 2;
				write(fd, &boyOrGirl, sizeof(int));
				close(fd);
			}
			fclose(file);
			exit(0);
		}
		else { // parinte
			int fd = open(NUME_FIFO, O_RDONLY);
			int boyOrGirl;
			read(fd, &boyOrGirl, sizeof(int));
			if(boyOrGirl == 0) {
				printf("Este fata!\n");
			}
			else {
				printf("Este baiat!\n");
			}
			close(fd);
			int statusPid;
			wait(&statusPid);
		}
	}
	unlink(NUME_FIFO);
	return 0;
}
