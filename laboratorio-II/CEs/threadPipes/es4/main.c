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
#define EOFS_STR "<<EOFS"

int string_compare(void *a, void *b)
{
    return (strcmp((char *)a, (char *)b) == 0);
}

int is_empty(const char *s)
{
    while (*s != '\0')
    {
        if (!isspace((unsigned char)*s))
            return 0;
        s++;
    }
    return 1;
}

void *THP(void *);
void *THW(void *);

typedef struct
{
    Queue_t *files;
    Queue_t *q;
    sem_t *sem;
    Queue_t *results;
} thp_t;

typedef struct
{
    Queue_t *q;
    Queue_t *results;
} thw_t;

typedef struct
{
    int col1;
    int col2;
} res_t;

int main(int argc, char const *argv[])
{
    int n = atoi(argv[1]);

    pthread_t produttore;
    pthread_t workers[n];

    thp_t *argP = malloc(sizeof(thp_t));
    thw_t *argW = malloc(sizeof(thw_t));
    Queue_t *fileQ = initQueue();
    Queue_t *resultsList = initQueue();
    Queue_t *fileList = initQueue();
    sem_t semp;
    sem_init(&semp, 0, 0);

    for (int i = 2; i < argc; i++)
    {
        push(fileList, strdup(argv[i]));
    }
    push(fileList, strdup(EOFS_STR));

    argP->results = resultsList;
    argP->files = fileList;
    argP->q = fileQ;
    argP->sem = &semp;

    argW->results = resultsList;
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

    printf("chiusi\n");
    sem_post(&semp);

    pthread_join(produttore, NULL);

    return 0;
}

void *THP(void *args)
{
    thp_t *stru = (thp_t *)args;
    char *fileName;
    while ((fileName = pop(stru->files)) != NULL)
    {
        if (string_compare(fileName, EOFS_STR))
            break;
        struct stat path_stat;
        stat(fileName, &path_stat);
        if (S_ISREG(path_stat.st_mode))
            push(stru->q, strdup(fileName));
    };
    push(stru->q, strdup(EOJ_STR));

    sem_wait(stru->sem);
    int final1 = 0, final2 = 0;
    void *read = NULL;
    res_t *readStruct = malloc(sizeof(res_t));
    while ((read = pop(stru->results)) != NULL)
    {
        if (string_compare((char *)read, EOJ_STR))
            break;

        readStruct = read;
        final1 += readStruct->col1;
        final2 += readStruct->col2;
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

    res_t *resStruct = NULL;
    while ((file = pop(stru->q)) != NULL)
    {
        printf("file: %s\n", file);
        if (string_compare(file, EOJ_STR))
            break;

        ptr = fopen(file, "r");
        if (ptr == NULL)
            break;

        while ((read = getline(&line, &len, ptr)) != -1)
        {
            if (is_empty(line))
                continue;
            printf("Line %s", line);
            char *token = strtok(line, ",");
            col1Val += atoi(token);
            token = strtok(NULL, ",");
            col2Val += atoi(token);
            printf("col1: %d - col2: %d\n", col1Val, col2Val);
        }
        resStruct = malloc(sizeof(res_t));
        printf("struct pointer: %p\n", &resStruct);
        resStruct->col1 = col1Val;
        resStruct->col2 = col2Val;
        col1Val = 0;
        col2Val = 0;
        push(stru->results, resStruct);
        printf("fine file: %s\n", file);
    }
    printf("out While\n");

    push(stru->results, EOJ_STR);
    push(stru->q, EOJ_STR);
    return NULL;
}