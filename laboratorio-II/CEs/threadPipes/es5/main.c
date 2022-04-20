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
#include <signal.h>
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
    int *signal;
    Queue_t *q;
} th1_t;
typedef struct
{
    int id;
    int *signal;
    Queue_t *q;
} th2_t;

typedef struct
{
    int *signal;
} thSignal_t;

void *TH1(void *);
void *TH2(void *);
void *THSignal(void *);
void sigHandler(int);

int main(int argc, char const *argv[])
{
    sigset_t maskSig;
    sigfillset(&maskSig);
    pthread_sigmask(SIG_BLOCK, &maskSig, NULL);

    int letts = 0;

    if (argc != 3)
        return 1;

    letts = atoi(argv[1]);
    int n = atoi(argv[2]);

    Queue_t *queue = initQueue();
    char *baseMsg = "messaggio!!";
    int signalVal = 0;
    pthread_t produttore;
    pthread_t threadSig;
    pthread_t lettore[letts];

    th1_t *argomentiProd = (th1_t *)malloc(sizeof(th1_t));
    th2_t *argomentiLett = (th2_t *)malloc(letts * sizeof(th2_t));
    argomentiProd->msgBase = strdup(baseMsg);
    argomentiProd->msgs = n;
    argomentiProd->q = queue;
    argomentiProd->signal = &signalVal;
    pthread_create(&produttore, NULL, TH1, argomentiProd);

    thSignal_t *argomentiSig = (thSignal_t *)malloc(sizeof(thSignal_t));
    argomentiSig->signal = &signalVal;
    pthread_create(&threadSig, NULL, THSignal, argomentiSig);

    for (int i = 0; i < letts; i++)
    {
        argomentiLett[i].q = queue;
        argomentiLett[i].id = i;
        argomentiLett[i].signal = &signalVal;
    }

    for (int i = 0; i < letts; i++)
    {
        pthread_create(&lettore[i], NULL, TH2, &argomentiLett[i]);
    }

    pthread_join(produttore, NULL);
    for (int i = 0; i < letts; i++)
        pthread_join(lettore[i], NULL);

    pthread_kill(threadSig, SIGUSR1);

    return 0;
}

void *TH1(void *args)
{
    sigset_t maskSig;
    sigfillset(&maskSig);
    pthread_sigmask(SIG_BLOCK, &maskSig, NULL);
    th1_t *stru = (th1_t *)args;
    char buff[200];
    for (int i = 0; i < stru->msgs; i++)
    {
        if (*stru->signal != 0)
        {
            printf("Scrittore - SEGNALE DI CHIUSURA\n");
            break;
        }
        sprintf(buff, "%s %d", stru->msgBase, i);
        push(stru->q, strdup(buff));
        sleep(2);
    }
    push(stru->q, strdup(EOJ_STR));

    return NULL;
}
void *TH2(void *args)
{
    sigset_t maskSig;
    sigfillset(&maskSig);
    pthread_sigmask(SIG_BLOCK, &maskSig, NULL);

    th2_t *stru = (th2_t *)args;
    char *line;
    while ((line = pop(stru->q)) != NULL)
    {
        if (*stru->signal != 0)
        {
            printf("Lettore id: %d - SEGNALE DI CHIUSURA\n", stru->id);
            break;
        }
        if (string_compare(line, EOJ_STR))
            break;
        printf("id: %d -> Ho letto: %s\n", stru->id, line);
    }
    push(stru->q, strdup(EOJ_STR));
    return NULL;
}

void *THSignal(void *args)
{
    thSignal_t *stru = (thSignal_t *)args;
    int signal;
    sigset_t maskSig;
    sigaddset(&maskSig, SIGINT);

    struct sigaction sa;
    sigaction(SIGQUIT, NULL, &sa);
    sa.sa_handler = &sigHandler;
    sigaction(SIGQUIT, &sa, NULL);

    for (;;)
    {
        sigwait(&maskSig, &signal);
        if (signal == SIGINT)
        {
            *stru->signal = 1;
            printf("\nMandato segnale di chiusura SIGINT!\n");
            fflush(stdout);
            return NULL;
        }
    }
}

void sigHandler(int val)
{
    printf("Arrivato Nella funzione");
    fflush(stdout);
    if (val == SIGQUIT)
    {
        printf("Arrivato il segnale QUIT");
        fflush(stdout);
    }
}