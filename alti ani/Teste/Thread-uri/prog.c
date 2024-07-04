#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


int number = 1;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int random_number(int min, int max)
{
    if (min == max)
        return min;
    else if (min > max)
    {
        int aux = min;
        min = max;
        max = aux;
    }

    //srand(time(NULL));
    return min + rand() % (max + 1 - min);
}

void generate_vector(int vect[], int size)
{
    int i, s;
    int n1, n2, aux;
    s = random_number (32, 64);

    // Generate ordered numbers
    for (i = 0; i < size; i++)
        vect[i] = i + 1;

    // Shuffle them
    for (i = 0; i < s; i++)
    {
        n1 = random_number (0, 4);
        n2 = random_number (0, 4);

        aux = vect[n1];
        vect[n1] = vect[n2];
        vect[n2] = aux;
    }
}

void* func(void* p)
{
    int i = *(int*)p;

    while (i != number)
    {
        //printf("%d %d\n", number, i);
    }

    printf ("[STATUS] Thread_ID:%d; v[i]:%d; Global_number:%d\n", pthread_self (), i, number);
    number += 1;
    pthread_exit (NULL);
}

int main()
{
    int i;
    int a[5];
    pthread_t t[5];

    srand (time (NULL));
    generate_vector (a, 5);

    printf ("The generated vector is: ");
    for (i = 0; i < 5; i++)
        printf ("%d ", a[i]);
    printf ("\n");

    for (i = 0; i < 5; i++)
        if (pthread_create (&t[i], NULL, func, &a[i]) < 0)
        {
            perror ("Error creating thread");
            exit (1);
        }

    for (i = 0; i < 5; i++)
        pthread_join (t[i], NULL);

    return 0;
}

