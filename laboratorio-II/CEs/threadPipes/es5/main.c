#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/time.h>
#include <ctype.h>
#include "unboundedqueue.h"

#define EOJ_STR "<<EOJ"

int string_compare(void *a, void *b)
{
    return (strcmp((char *)a, (char *)b) == 0);
}

typedef struct
{
    char *msgBase;
    int msgs;
    Queue_t *q;
} th1_t;
typedef struct
{
    int id;
    Queue_t *q;
} th2_t;

void *TH1(void *);
void *TH2(void *);

int main(int argc, char const *argv[])
{
    int letts = 0;

    if (argc != 2)
        return 1;

    letts = argv[1];

    Queue_t *queue = initQueue();
    char *baseMsg = "messaggio!!";
    int n = 15;

    pthread_t produttore;
    pthread_t lettore[letts];

    th1_t *argomentiProd = (th1_t *)malloc(sizeof(th1_t));

    argomentiProd->msgBase = strdup(baseMsg);
    argomentiProd->msgs = n;
    argomentiProd->q = queue;

    pthread_create(&produttore, NULL, TH1, argomentiProd);

    for (int i = 0; i < letts; i++)
    {
        th2_t *argomentiLett = (th1_t *)malloc(sizeof(th2_t));
        argomentiLett->q = queue;
        argomentiLett->id = i;
        pthread_create(&lettore[i], NULL, TH2, argomentiLett);
    }

    pthread_join(produttore, NULL);
    for (int i = 0; i < letts; i++)
        pthread_join(lettore, NULL);
        
    return 0;
}

void *TH1(void *args)
{
    th1_t *stru = (th1_t *)args;
    char buff[200];
    for (int i = 0; i < stru->msgs; i++)
    {
        sprintf(buff, "%s %d", stru->msgBase, i);
        push(stru->q, strdup(buff));
        sleep(2);
    }
    push(stru->q, strdup(EOJ_STR));

    return NULL;
}
void *TH2(void *args)
{
    th2_t *stru = (th2_t *)args;
    char *line;
    while ((line = pop(stru->q)) != NULL)
    {
        if (string_compare(line, EOJ_STR))
            break;
        printf("id: %d -> Ho letto: %s\n", stru->id, line);
    }
    push(stru->q, strdup(EOJ_STR));
    return NULL;
}