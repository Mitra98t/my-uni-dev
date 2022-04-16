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
    Queue_t *q;
} th1_t;

int main(int argc, char const *argv[])
{
    if (argc != 4)
        return 1;

    int m = atoi(argv[1]), n = atoi(argv[2]), k = atoi(argv[3]);

    pthread_t scrittori[m];
    pthread_t lettori[n];

    Queue_t *que = initQueue();

    int start = 0, chunk = k / m, r = k % m;
    th1_t *args1 = (th1_t *)malloc(sizeof(th1_t));
    args1->q = que;
    for (int i = 0; i < m; i++)
    {
        args1->start = start;
        args1->stop = args1->start + chunk + (i < r ? 1 : 0);
        pthread_create(&scrittori[i], NULL, TH1, args1);
        start = args1->stop;
    }
    for (int i = 0; i < n; i++)
    {
        pthread_create(&lettori[i], NULL, TH1, que);
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
    for (int i = stru->start; i < stru->stop; i++)
    {
        sprintf(buffer, "Th: %ld --- msg: %d\n", pthread_self(), i);
        push(stru->q, buffer);
    }
    return NULL;
}

void *TH2(void *args)
{
    Queue_t *q1 = (Queue_t *)args;
    char *line = NULL;
    int letti = 0;
    for (;;)
    {
        line = strdup(pop(q1));
        if (string_compare(line, EOF_STR))
            return NULL;

        printf("#%d - lett %ld: %s\n", letti, pthread_self(), line);
        fflush(stdout);
    }
    return NULL;
}
