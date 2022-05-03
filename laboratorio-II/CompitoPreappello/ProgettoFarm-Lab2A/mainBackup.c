#include <util.h>
#include <errno.h>
#include <dirent.h>
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

#include "boundedqueue.h"
#include "util.h"

#define EOJ_STR "<<EOJ"

int string_compare(void *a, void *b)
{
    return (strcmp((char *)a, (char *)b) == 0);
}

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

typedef struct
{
    int filesCount;
    int t;
    char **files;
    BQueue_t *q;
} mTh_t;

typedef struct
{
    BQueue_t *q;
} wTh_t;

void *masterTH(void *);
void *workerTH(void *);

int main(int argc, char const *argv[])
{

    int n = 4;
    int q = 8;
    int t = 0;

    char **files = NULL;
    int fileCount = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0)
        {
            n = atoi(argv[i + 1]);
            i++;
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            t = atoi(argv[i + 1]);
            i++;
        }
        else if (strcmp(argv[i], "-q") == 0)
        {
            q = atoi(argv[i + 1]);
            i++;
        }
        else
        {
            files = realloc(files, sizeof(char) * 255);
            files[fileCount] = strdup(argv[i]);
            fileCount++;
        }
    }

    printf("n: %d - q: %d - t: %d\n", n, q, t);

    for (int i = 0; i < fileCount; i++)
    {
        printf("%s\n", files[i]);
    }

    pid_t pid;
    int status;
    switch (pid = fork())
    {
    case -1:
        perror("cannot fork");
        break;
    case 0:
    {
        // PADRE
        BQueue_t *queue = initBQueue(n);
        pthread_t masterThread;
        pthread_t workerThread[n];
        mTh_t *argMaster = (mTh_t *)malloc(sizeof(mTh_t));
        wTh_t *argWorkers = (wTh_t *)malloc(n * sizeof(wTh_t));

        for (int i = 0; i < n; i++)
        {
            argWorkers[i].q = queue;
        }

        argMaster->files = files;
        argMaster->filesCount = fileCount;
        argMaster->q = queue;
        argMaster->t = t;

        pthread_create(&masterThread, NULL, masterTH, argMaster);

        for (int i = 0; i < n; i++)
        {
            pthread_create(&workerThread[i], NULL, workerTH, &argWorkers[i]);
        }

        pthread_join(masterThread, NULL);
        for (int i = 0; i < n; i++)
        {
            pthread_join(workerThread[i], NULL);
        }
        break;
    }
    default:
        // FIGLIO
        
        break;
    }

    return 0;
}

void *masterTH(void *args)
{
    mTh_t *stru = (mTh_t *)args;

    for (int i = 0; i < stru->filesCount; i++)
    {
        if (is_regular_file(stru->files[i]))
        {
            push(stru->q, strdup(stru->files[i]));
            printf("pushing file: %s\n", stru->files[i]);
            usleep(stru->t * 1000);
        }
    }

    push(stru->q, EOJ_STR);
    return NULL;
}

void *workerTH(void *args)
{
    wTh_t *stru = (wTh_t *)args;

    FILE *ptr = NULL;
    char *filePath = NULL;
    ssize_t readB;
    long *temp;
    temp = (long *)malloc(sizeof(long));
    int numCount = 0;
    long result = 0;

    while ((filePath = pop(stru->q)) != NULL)
    {
        printf("Read: %s\n", filePath);
        if (string_compare(filePath, EOJ_STR))
            break;
        numCount = 0;
        result = 0;
        ptr = fopen(filePath, "r");
        while ((readB = fread(temp, sizeof(long), 1, ptr)) != 0)
        {
            result += numCount * (*temp);
            numCount++;
        }

        printf("File: %s - Result: %ld\n", filePath, result);
        fclose(ptr);
    }
    push(stru->q, EOJ_STR);
    return NULL;
}

/*
file1.dat -> 945
file2.dat -> 225
*/