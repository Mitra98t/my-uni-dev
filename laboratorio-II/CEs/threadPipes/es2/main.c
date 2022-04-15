#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/time.h>
#include <ctype.h>
#include "unboundedqueue.h"
#include "icl_hash.h"

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
    icl_hash_t *ht;
    sem_t *sem;
    int *errF;
} argTh2;

typedef struct
{
    icl_hash_t *ht;
    sem_t *sem;
    int *errF;
} argTh3;

int main(int argc, char const *argv[])
{
    if (argc != 2)
        return 1;
    char *file = strdup(argv[1]);
    pthread_t threads[3];
    Queue_t *q1 = initQueue();
    Queue_t *q2 = initQueue();
    icl_hash_t *ht = icl_hash_create(100, hash_pjw, string_compare);
    sem_t semp;
    sem_init(&semp, 0, 0);
    int errFB = 0;

    argTh1 *args1 = (argTh1 *)malloc(sizeof(argTh1));
    args1->file = strdup(file);
    args1->q1 = q1;
    pthread_create(&threads[0], NULL, TH1, args1);

    argTh2 *args2 = (argTh2 *)malloc(sizeof(argTh2));
    args2->q1 = q1;
    args2->ht = ht;
    args2->sem = &semp;
    args2->errF = &errFB;
    pthread_create(&threads[1], NULL, TH2, args2);

    argTh3 *args3 = (argTh3 *)malloc(sizeof(argTh3));
    args3->ht = ht;
    args3->sem = &semp;
    args3->errF = &errFB;
    pthread_create(&threads[2], NULL, TH3, args3);

    for (int i = 0; i < 3; i++)
    {
        pthread_join(threads[i], NULL);
    }

    deleteQueue(q1);
    deleteQueue(q2);
    return 0;
}

void *TH1(void *args)
{
    FILE *ptr;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    argTh1 *stru = (argTh1 *)args;

    ptr = fopen(stru->file, "r");

    if (ptr == NULL)
    {
        push(stru->q1, "<<ERROR");
        return NULL;
    }

    while ((read = getline(&line, &len, ptr)) != -1)
    {
        push(stru->q1, strdup(line));
    }

    push(stru->q1, "<<EOF");
    fclose(ptr);
    if (line)
        free(line);

    return NULL;
}
void *TH2(void *args)
{
    argTh2 *stru = (argTh2 *)args;
    char *line = NULL;

    const char s[2] = " ";

    while ((line = strdup(pop(stru->q1))) != NULL)
    {
        if (strcmp(line, "<<ERROR") == 0)
        {
            *(stru->errF) = 1;
            sem_post(stru->sem);
            return NULL;
        }
        if (strcmp(line, "<<EOF") == 0)
            break;
        char *token;

        /* get the first token */
        token = strtok(line, s);

        /* walk through other tokens */
        while (token != NULL)
        {
            token[strcspn(token, "\n")] = 0;
            if (!is_empty(token))
                icl_hash_insert(stru->ht, (void *)token, (void *)token);
            token = strtok(NULL, s);
        }
    }
    sem_post(stru->sem);

    return NULL;
}
void *TH3(void *args)
{
    icl_entry_t *bucket, *curr;
    argTh3 *stru = (argTh3 *)args;
    char *line = NULL;
    sem_wait(stru->sem);

    if (*(stru->errF))
        return NULL;

    for (int i = 0; i < stru->ht->nbuckets; i++)
    {
        if (stru->ht->buckets[i] != NULL)
        {
            printf("%s\n", (char *)stru->ht->buckets[i]->key);
            fflush(stdout);
        }
    }
    return NULL;
}
