#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>

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

    srand (time (NULL));
    return min + rand() % (max + 1 - min);
}

int main(int argc, char *argv[])
{
    int fifo1, fifo2;
    int n, rez;

    if (mkfifo ("./fifo-file2", 0600) < 0)
    {
        perror ("Error creating fifo-file2");
        exit (2);
    }

    fifo1 = open ("./fifo-file1", O_RDONLY);
    fifo2 = open ("./fifo-file2", O_WRONLY);

    if (read (fifo1, &n, sizeof (int)) < 0)
    {
        perror ("Error reading from fifo-file1");
        exit (1);
    }
    printf ("Red %d from file-fifo1\n", n);

    n += random_number(1, 10);

    printf ("Changed number to %d\n", n);

    if (n % 2 == 0)
        rez = -1;
    else
        rez = n;

    if (write (fifo2, &rez, sizeof (int)) < 0)
    {
        perror ("Error writing in fifo-file2");
        exit (2);
    }
    printf ("Wrote %d to file-fifo2\n", rez);

    close (fifo1);
    close (fifo2);
    unlink ("./fifo-file2");

    if (rez == -1)
        printf ("Finished -- I WON, MAN!!!\n");
    else
        printf ("Finished\n");
    return 0;
}
