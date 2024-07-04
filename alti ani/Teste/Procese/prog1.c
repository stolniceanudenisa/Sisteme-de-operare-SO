#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
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

    srand(time(NULL));
    return min + rand() % (max + 1 - min);
}

int main()
{
    int fifo1, fifo2;
    int n = random_number (10, 2000);

    //printf ("My PID is %d", getpid());

    if (mkfifo ("./fifo-file1", 0600) < 0)
    {
        perror ("Error creating fifo-file1");
        exit (1);
    }

    //if (mkfifo ("./fifo-file2", 0600) < 0)
    //{
    //    perror ("Error creating fifo-file2");
    //    exit (2);
    //}

    while (n != -1)
    {
    fifo1 = open ("./fifo-file1", O_WRONLY);
    fifo2 = open ("./fifo-file2", O_RDONLY);

    //while (n != -1)
    //{
        if (write (fifo1, &n, sizeof(int)) < 0)
        {
            perror ("Error writing in fifo-file1");
            exit (1);
        }
        printf ("Wrote %d to file-fifo1\n", n);

        if (read (fifo2, &n, sizeof(int)) < 0)
        {
            perror ("Error reading from fifo-file2");
            exit (2);
        }
        printf ("Red %d from file-fifo2\n", n);
    //}

    //printf ("Terminating...\n");

    close (fifo1);
    close (fifo2);
    }
    unlink ("./fifo-file1");
    //unlink ("./fifo-file2");

    printf ("Finished\n");
    return 0;
}

