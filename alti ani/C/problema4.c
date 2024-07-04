#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

// Să se scrie un program C care creează un proces copil cu care 
// comunică prin pipe.
// Procesul părinte citeşte de la tastatură două numere întregi pe 
// care le trimite prin pipe procesului copil,
// iar procesul copil returnează prin pipe suma lor.

int main(int argc, char* argv[]) {
	int fdp[2];
	if(pipe(fdp) == -1) {
		fprintf(stderr, "eroare la pipe()");
		return 1;
	}
	pid_t pid = fork();
	if(pid == -1) { // eroare
		fprintf(stderr, "eroare la fork()");
		exit(1);
	} else if(pid == 0) { // c8chil
		int number1, number2;
		read(fdp[0],&number1,sizeof(int));
		read(fdp[0],&number2,sizeof(int));
		close(fdp[0]);
		int sum = number1 + number2;
		write(fdp[1],&sum,sizeof(int));
		close(fdp[1]);
	} else { // parent
		int number1, number2;
		scanf("%d", &number1);
		scanf("%d", &number2);
		write(fdp[1],&number1,sizeof(int));
		write(fdp[1],&number2,sizeof(int));
		close(fdp[1]); // 1 write
		int status;
		wait(&status);
		int sum;
		read(fdp[0],&sum,sizeof(int));
		printf("suma este %d\n", sum);
		close(fdp[0]); // 0 read
	}
	return 0;
}
