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

void *THP(void *);
void *THW(void *);

typedef struct
{
    char *files;
    Queue_t *q;
    sem_t *sem;
    Queue_t *col1;
    Queue_t *col2;
} thp_t;
typedef struct
{
    Queue_t *q;
    Queue_t *col1;
    Queue_t *col2;
} thw_t;

int main(int argc, char const *argv[])
{
    int n = atoi(argv[1]);

    pthread_t produttore;
    pthread_t workers[n];

    thp_t *argP = malloc(sizeof(thp_t));
    thw_t *argW = malloc(sizeof(thw_t));
    Queue_t *fileQ = initQueue();
    Queue_t *col1Q = initQueue();
    Queue_t *col2Q = initQueue();
    char *fileList = "";
    sem_t semp;
    sem_init(&semp, 0, 0);

    for (int i = 2; i < argc; i++)
    {
        strcat(fileList, argv[i]);
        if (i + 1 != argc)
            strcat(fileList, "|");
    }

    argP->col1 = col1Q;
    argP->col2 = col2Q;
    argP->files = strdup(fileList);
    argP->q = fileQ;
    argP->sem = &semp;

    argW->col1 = col1Q;
    argW->col2 = col2Q;
    argW->q = fileQ;

    pthread_create(&produttore, NULL, THP, argP);

    for (int i = 0; i < n; i++)
    {
        pthread_create(&workers[i], NULL, THW, argW);
    }

    for (int i = 0; i < n; i++)
    {
        pthread_join(workers[i], NULL);
    }

    sem_post(&semp);

    pthread_join(produttore, NULL);

    return 0;
}

void *THP(void *args)
{
    thp_t *stru = (thp_t *)args;
    char *token = strtok(stru->files, "|");
    while (token != NULL)
    {
        struct stat path_stat;
        stat(token, &path_stat);
        if (S_ISREG(path_stat.st_mode))
            push(stru->q, strdup(token));
        token = strtok(NULL, "|");
    }

    push(stru->q, EOJ_STR);

    sem_wait(stru->sem);
    int final1 = 0, final2 = 0;
    char *read = NULL;
    while ((read = pop(stru->col1)) != NULL)
    {
        final1 += atoi(read);
    }
    while ((read = pop(stru->col1)) != NULL)
    {
        final2 += atoi(read);
    }
    printf("Colonna 1: %d - Colonna 2: %d\n", final1, final2);
    fflush(stdout);
    return NULL;
}
void *THW(void *args)
{
    thw_t *stru = (thw_t *)args;
    FILE *ptr;
    char *file = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int col1Val = 0, col2Val = 0;
    while ((file = pop(stru->q)) != NULL)
    {
        if (string_compare(file, EOJ_STR))
            break;

        ptr = fopen(file, "r");
        if (ptr == NULL)
            break;

        while ((read = getline(&line, &len, ptr)) != -1)
        {
            char *token = strtok(line, ",");
            col1Val += atoi(token);
            token = strtok(NULL, ",");
            col2Val += atoi(token);
        }
        push(stru->col1, (void *)col1Val);
        push(stru->col2, (void *)col2Val);
    }
    push(stru->q, EOJ_STR);
    return NULL;
}