#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NBUFF 10
#define MAXNTHREADS 20

int nitems, npg;

struct
{
    int buff[NBUFF];
    int nput;
    int nputval;
    sem_t mutex, nempty, nstored;
} shared;

void *PG(), *PS();

int main(int argc, char **argv)
{
    int i;
    pthread_t tid_PG[MAXNTHREADS], tid_PS;

    if (argc != 3)
        exit(2);
    nitems = atoi(argv[1]);
    npg = atoi(argv[2]) > MAXNTHREADS ? MAXNTHREADS : atoi(argv[2]);

    /* initialize semaphores */
    sem_init(&shared.mutex, 0, 1);
    sem_init(&shared.nempty, 0, NBUFF);
    sem_init(&shared.nstored, 0, 0);

    /* create PG and PS */
    for (i = 0; i < npg; i++)
    {
        pthread_create(&tid_PG[i], NULL, PG, NULL);
    }
    pthread_create(&tid_PS, NULL, PS, NULL);

    /* wait for end */
    for (i = 0; i < npg; i++)
    {
        pthread_join(tid_PG[i], NULL);
    }
    pthread_join(tid_PS, NULL);

    /* end work */
    sem_destroy(&shared.mutex);
    sem_destroy(&shared.nempty);
    sem_destroy(&shared.nstored);

    exit(0);
}

void *
PG()
{
    for (;;)
    {
        sem_wait(&shared.nempty);
        sem_wait(&shared.mutex);

        if (shared.nput >= nitems)
        {
            sem_post(&shared.nempty);
            sem_post(&shared.mutex);
            return (NULL);
        }

        /* generate int number */
        shared.buff[shared.nput % NBUFF] = shared.nputval;
        shared.nput++;
        shared.nputval++;

        usleep(100);
        sem_post(&shared.mutex);
        sem_post(&shared.nstored);
    }
}

void *
PS()
{
    int i;

    FILE *fpWrite = fopen("data.txt", "w");
    for (i = 0; i < nitems; i++)
    {
        sem_wait(&shared.nstored);
        sem_wait(&shared.mutex);

        /*dosomething()*/
        fprintf(fpWrite, "%d", shared.buff[i % NBUFF]);
        usleep(100);
        sem_post(&shared.mutex);
        sem_post(&shared.nempty);
    }
    fclose(fpWrite);
    return NULL;
}