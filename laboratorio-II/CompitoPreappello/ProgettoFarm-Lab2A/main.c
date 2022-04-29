#include <stdlib.h>
#include <stdio.h>
#include <util.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#include "boundedqueue.h"
#include "util.h"

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

    BQueue_t *queue = initBQueue(n);

    pthread_t masterThread;
    mTh_t *argMaster = (mTh_t *)malloc(sizeof(mTh_t));

    argMaster->files = files;
    argMaster->filesCount = fileCount;
    argMaster->q = queue;
    argMaster->t = t;

    pthread_create(&masterThread, NULL, masterTH, argMaster);

    pthread_join(masterThread, NULL);
    return 0;
}

void *masterTH(void *args)
{
    mTh_t *stru = (mTh_t *)args;

    for (int i = 0; i < stru->filesCount; i++)
    {
        is_regular_file(stru->files[i]);
        push(stru->q, stru->files[i]);
        printf("pushing file: %s\n", stru->files[i]);
        usleep(stru->t * 1000);
    }

    return NULL;
}

void *workerTH(void *args)
{

}