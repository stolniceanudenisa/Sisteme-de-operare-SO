// Să se scrie un program client-server care implementează
// TVA-ul. Clientul transmite serverului un preț, iar acesta
// returnează prețul cu tot cu TVA. (TVA = 24% din prețul
// inițial). Clientul va afișa rezultatul primit. Pentru o
// rezolvare completă, trebuie tratate și excepțiile.

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#define NUME_FIFO "pipe.fifo"

int main(int argc, char *argv[]) {
	int fd = open(NUME_FIFO, O_WRONLY);
	if(fd == -1) {
		printf("eroare la open()\n");
		return 1;
	}
	int pret;
	scanf("%d", &pret);
	printf("Pret: %d\n", pret); 
	write(fd, &pret, sizeof(int));
	close(fd);
	fd = open(NUME_FIFO, O_RDONLY);
	if(fd == -1) {
		printf("eroare la open()\n");
		return 1;
	}
	double pretTVA;
	read(fd, &pretTVA, sizeof(double));
	printf("Pret cu TVA: %f\n", pretTVA);
	close(fd);
	unlink(NUME_FIFO);
	return 0;
}
