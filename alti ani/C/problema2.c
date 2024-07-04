#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NUME_FIFO "pipe.fifo"

// Să se scrie un program C care creează un proces copil cu care 
// comunică prin pipe.
// Procesul părinte citeşte de la tastatură un număr natural şi îl 
// trimite prin pipe procesului copil,
// iar procesul copil verifică şi afişează dacă acest număr este 
// prim.

int main(int argc, char* argv[]) {
	int status = mkfifo(NUME_FIFO,0666);
	if(status == -1) {
		fprintf(stderr, "eroare la mkfifo()");
		return 1;
	}
	pid_t pid = fork();
	if(pid < 0) {
		fprintf(stderr, "eroare la fork()");
		return 1;
	}
	else if(pid == 0) {
		int fd = open(NUME_FIFO, O_RDONLY);
		if(fd == -1) {
			fprintf(stderr, "eroare la open()");
			return 1;
		}
		int number;
		read(fd, &number, sizeof(int));
		int d = 2, ok = 1;
		while(d <= number /2) {
			if(number % d == 0) {
				ok = 0;
				number = number / d;
			}
			d++;
		}
		if(ok == 1) {
			printf("este prim\n");
		}
		else {
			printf("nu este prim\n");
		}
	} else {
		int number;
		scanf("%d", &number);
		int fd = open(NUME_FIFO, O_WRONLY);
		if(fd == -1) {
			fprintf(stderr, "eroare la open()");
			return 1;
		}
		write(fd, &number, sizeof(int));
		close(fd);
	}
	unlink(NUME_FIFO);
	return 0;
}
