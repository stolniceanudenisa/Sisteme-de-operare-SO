#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

/*
	Sa se scrie un program care avand definit un vector de numere,creeaza 3 threaduri care:

	- primul thread calculeaza suma numerelor din vector de pe pozitii de forma 3*k (multiplu de 3), ex v[0],v[3],...

	- al doilea thread calculeaza suma numerelor din vector de pe pozitii de forma 3*k+1 (multiplu de 3 +1), ex v[1],v[4],...

	- al treilea thread calculeaza suma numerelor din vector de pe pozitii de forma 3*k+2 (multiplu de 3 +2)	

	*(cine a terminat prima parte) Threadurile sa adauge la sfarsit suma calculata la o suma globala. Programul pincipal afiseaza suma totala a vectorului.

*/

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
long s = 0;
int v[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

void *sum1(void *);
void *sum2(void *);
void *sum3(void *);

int main()
{
	void *value;
	pthread_t t[3];
	
	if (pthread_create (&t[0], NULL, sum1, &v) < 0)
	{
		perror ("Error at sum #1!");
		exit(1);
	}
	
	pthread_join (t[0], &value);
	s = s + (long)value;
	printf ("Sum #1 is: %lu \n", (long)value);

	if (pthread_create(&t[1], NULL, sum2, &v) < 0)
	{
		perror("Error at sum #2!");
		exit(2);
	}
	
	pthread_join (t[1], &value);
	s = s + (long)value;
	printf("Sum #2 is: %lu \n", (long)value);

	if (pthread_create(&t[2], NULL, sum3, &v) < 0) {
		perror("Error at sum #3!");
		exit(3);
	}
	
	pthread_join(t[2], &value);
	printf("Sum #3 is: %lu \n", (long)value);
	s = s + (long)value;
	
	printf("Sum total is: %lu \n", s);
	return 0;
}

void *sum1(void *p)
{
	long s1 = 0, i;
	int *c = (int *)p;
	
	for (i = 0; i < 9; i++)
	{
		pthread_mutex_lock(&m);
		
		if (i % 3 == 0)
			s1 = s1 + *(c + i);
			
		pthread_mutex_unlock(&m);
	}
	
	return (void *)s1;
}

void *sum2(void *p)
{
	long s2 = 0, i;
	int *c = (int *)p;
	
	for (i = 0; i < 9; i++)
	{
		pthread_mutex_lock(&m);
		
		if (i % 3 == 1)
			s2 = s2 + *(c + i);
			
		pthread_mutex_unlock(&m);
	}
	
	return (void *)s2;
}

void *sum3(void *p)
{
	long s3 = 0, i;
	int *c = (int *)p;
	
	for (i = 0; i < 9; i++)
	{
		pthread_mutex_lock(&m);
		
		if (i % 3 == 2)
			s3 = s3 + *(c + i);
			
		pthread_mutex_unlock(&m);
	}
	
	return (void *)s3;
}
