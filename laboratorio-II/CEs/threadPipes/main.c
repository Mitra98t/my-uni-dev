#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include "unboundedqueue.h"

void *TH1(void *);
void *TH2(void *);
void *TH3(void *);

typedef struct
{
    char *file;
    Queue_t *q1;
} argTh1;

typedef struct
{
    Queue_t *q1;
    Queue_t *q2;
} argTh2;

int main(int argc, char const *argv[])
{
    if (argc != 2)
        return 1;
    char *file = argv[1];
    pthread_t threads[3];
    Queue_t *q1 = initQueue();
    Queue_t *q2 = initQueue();

    argTh1 *args1 = (argTh1 *)malloc(sizeof(argTh1));
    args1->file = file;
    args1->q1 = q1;
    pthread_create(threads[0], NULL, TH1, args1);

    argTh2 *args2 = (argTh2 *)malloc(sizeof(argTh2));
    args2->q1 = q1;
    args2->q2 = q2;
    pthread_create(threads[0], NULL, TH2, args2);

    pthread_create(threads[0], NULL, TH3, q2);

    return 0;
}

void *TH1(void *args)
{
    FILE *ptr;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    argTh1 *stru = (argTh1 *)args;
    ptr = fopen(stru->file, 'r');

    if (ptr == NULL)
    {
        push(stru->q1, "<<ERROR");
        return 1;
    }

    while ((read = getline(&line, &len, ptr)) != -1)
    {
        push(stru->q1, line);
    }

    push(stru->q1, "<<EOF");
    fclose(ptr);
    if (line)
        free(line);

    return 0;
}
void *TH2(void *args)
{
    argTh2 *stru = (argTh2 *)args;
    char *line = NULL;

    const char s[2] = " ";

    while ((line = pop(stru->q2)) != NULL)
    {
        if (strcmp(line, "<<ERROR") == 0)
        {
            push(stru->q2, "<<ERROR");
            return 1;
        }
        if (strcmp(line, "<<EOF") == 0)
        {
            push(stru->q2, "<<EOF");
            break;
        }
        char *token;

        /* get the first token */
        token = strtok(line, s);

        /* walk through other tokens */
        while (token != NULL)
        {
            push(stru->q2, token);

            token = strtok(NULL, s);
        }
    }
    return 0;
}
void *TH3(void *args)
{
    Queue_t *q2 = (Queue_t *)args;
    char *line = NULL;
    while ((line = pop(q2)) != NULL)
    {
        if (strcmp(line, "<<ERROR") == 0)
        {
            return 1;
        }
        if (strcmp(line, "<<EOF") == 0)
            break;

        printf("%s\n", line);
    }
    return 0;
}
