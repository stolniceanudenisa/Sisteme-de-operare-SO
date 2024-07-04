#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Să se scrie un program C care creează un proces copil cu care 
// comunică prin pipe.
// Procesul părinte citeşte de la tastatură un număr natural şi îl
// trimite prin pipe procesului copil,
// iar procesul copil verifică şi afişează dacă acest număr este par 
// sau impar.

int main(int argc, char* argv[]) {
	int fdp[2];
	if(pipe(fdp) == -1) {
		fprintf(stderr, "eroare la pipe()");
	}
	pid_t pid = fork();
	if(pid < 0) {
		fprintf(stderr, "eroare la fork()");
		exit(1);
	} else if(pid == 0) {
		close(fdp[1]);
		int number;
		read(fdp[0],&number,sizeof(int));
		if(number % 2 == 0) {
			printf("Este par!\n");
		}
		else {
			printf("Este impar!\n");
		}
		close(fdp[0]);
	} else {
		close(fdp[0]);
		int number;
		scanf("%d", &number);
		write(fdp[1],&number,sizeof(int));
		close(fdp[1]);
	}
	return 0;
}
