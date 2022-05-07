#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "unboundedqueue.h"

#define EOF_STR "<<EOF"

int string_compare(void *a, void *b)
{
    return (strcmp((char *)a, (char *)b) == 0);
}

void *TH1(void *);
void *TH2(void *);

typedef struct
{
    int start;
    int stop;
    int id;
    Queue_t *q;
} th1_t;
typedef struct
{
    int id;
    Queue_t *q;
} th2_t;

int main(int argc, char const *argv[])
{
    if (argc != 4)
        return 1;

    int m = atoi(argv[1]), n = atoi(argv[2]), k = atoi(argv[3]);

    pthread_t scrittori[m];
    pthread_t lettori[n];

    Queue_t *que = initQueue();

    int start = 0, chunk = k / m, r = k % m;
    th1_t *argsThreads = malloc(m * sizeof(th1_t));
    th2_t *args2Threads = malloc(n * sizeof(th2_t));
    printf("CHUNK: %d - RESTO: %d\n", chunk, r);
    for (int i = 0; i < m; ++i)
    {
        argsThreads[i].id = i;
        argsThreads[i].q = que;
        argsThreads[i].start = start;
        argsThreads[i].stop = start + chunk + ((i < r) ? 1 : 0);
        start = argsThreads[i].stop;
    }
    for (int i = 0; i < n; ++i)
    {
        args2Threads[i].id = i;
        args2Threads[i].q = que;
    }

    for (int i = 0; i < m; i++)
    {
        pthread_create(&scrittori[i], NULL, TH1, &argsThreads[i]);
    }
    for (int i = 0; i < n; i++)
    {
        pthread_create(&lettori[i], NULL, TH2, &args2Threads[i]);
    }

    for (int i = 0; i < m; i++)
    {
        pthread_join(scrittori[i], NULL);
    }
    for (int i = 0; i < n; i++)
    {
        push(que, EOF_STR);
    }

    for (int i = 0; i < n; i++)
    {
        pthread_join(lettori[i], NULL);
    }

    deleteQueue(que);

    return 0;
}

void *TH1(void *args)
{
    th1_t *stru = (th1_t *)args;
    // char *str = "Th: ";
    char buffer[100];

    printf("SCRITTORE id%d - start: %d - stop: %d\n", stru->id, stru->start, stru->stop);

    for (int i = stru->start; i < stru->stop; i++)
    {
        sprintf(buffer, "Th: id%d --- msg: %d\n", stru->id, i);
        push(stru->q, strdup(buffer));
    }
    return NULL;
}

void *TH2(void *args)
{
    th2_t *stru = (th2_t *)args;
    char *line = NULL;
    int letti = 0;
    for (;;)
    {
        line = strdup(pop(stru->q));
        if (string_compare(line, EOF_STR))
            return NULL;

        letti++;

        printf("#%d - th: id%d ---> MESSAGGIO: %s\n", letti, stru->id, line);
        fflush(stdout);
    }
    return NULL;
}
