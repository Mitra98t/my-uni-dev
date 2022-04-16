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
    int n;
    int msg;
    Queue_t *qs[];
} th1_t;

int main(int argc, char const *argv[])
{
    printf("we");
    if (argc != 3)
        return 1;

    int m = atoi(argv[1]), n = atoi(argv[2]), k = 1;

    if (argc == 4)
        k = atoi(argv[3]);

    pthread_t scrittori[m];
    pthread_t lettori[n];

    // Queue_t *qsList[n];
    // for (int i = 0; i < n; i++)
    // {
    //     qsList[i] = initQueue();
    // }

    th1_t *args1 = (th1_t *)malloc(sizeof(th1_t));
    for (int i = 0; i < n; i++)
    {
        args1->qs[i] = initQueue();
    }
    // args1->qs = &qsList;
    args1->n = n;
    args1->msg = k / m;

    for (int i = 0; i < m; i++)
    {
        printf("creating SCRITTORE %d", i);
        pthread_create(&scrittori[i], NULL, TH1, args1);
    }
    for (int i = 0; i < n; i++)
    {
        printf("creating LETTORE %d", i);
        pthread_create(&lettori[i], NULL, TH1, args1->qs[i]);
    }

    for (int i = 0; i < m; i++)
    {
        pthread_join(scrittori[i], NULL);
    }
    for (int i = 0; i < n; i++)
    {
        pthread_join(lettori[i], NULL);
    }

    for (int i = 0; i < n; i++)
    {
        deleteQueue(args1->qs[i]);
    }

    return 0;
}

void *TH1(void *args)
{
    th1_t *stru = (th1_t *)args;
    // char *str = "Th: ";
    char buffer[100];
    for (int i = 0; i < stru->msg; i++)
    {
        sprintf(buffer, "Th: %ld --- msg: %d\n", pthread_self(), i);
        // strcat(str, pthread_self());
        // strcat(str, " messaggio: ");
        // strcat(str, i);
        for (int j = 0; j < stru->n; j++)
        {
            push(stru->qs[j], "ciao");
        }
        // str = strdup("Th: ");
    }
    for (int j = 0; j < stru->n; j++)
    {
        push(stru->qs[j], EOF_STR);
    }
    return NULL;
}

void *TH2(void *args)
{
    Queue_t *q1 = (Queue_t *)args;
    char *line = NULL;
    while ((line = strdup(pop(q1))) != NULL)
    {
        if (string_compare(line, EOF_STR))
            return NULL;

        printf("lett %ld: %s\n", pthread_self(), line);
        fflush(stdout);
    }
    return NULL;
}
