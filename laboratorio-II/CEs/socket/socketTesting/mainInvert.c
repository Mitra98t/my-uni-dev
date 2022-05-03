#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

#define UNIX_PATH_MAX 108 /* man 7 unix */
#define MAX_MSG_LEN 256
#define MSG_NUM 2
#define SOCKNAME "./mysockInverted"
#define N 100
#define CLIENTS_NUM 5

void *clientTH(void *);
void *serverWorkerTH(void *);

typedef struct
{
    struct sockaddr_un sa;
    char *msg;
    int id;
} cTh_t;

typedef struct
{
    int fdc;
    int id;
} sTh_t;

int main(void)
{
    int fd_skt, fd_c;
    // char buf[N];
    struct sockaddr_un sa;
    strncpy(sa.sun_path, SOCKNAME, UNIX_PATH_MAX);
    sa.sun_family = AF_UNIX;

    if (fork() != 0)
    { /* padre, client */
        pthread_t clients[CLIENTS_NUM];
        cTh_t *argsClient = (cTh_t *)malloc(sizeof(cTh_t) * CLIENTS_NUM);
        for (int i = 0; i < CLIENTS_NUM; i++)
        {
            argsClient[i].id = i;
            argsClient[i].msg = strdup("Hallo!");
            argsClient[i].sa = sa;
        }

        for (int i = 0; i < CLIENTS_NUM; i++)
        {
            pthread_create(&clients[i], NULL, clientTH, &argsClient[i]);
        }

        for (int i = 0; i < CLIENTS_NUM; i++)
        {
            pthread_join(clients[i], NULL);
        }
        // printf("chiusura clients\n");
        unlink(SOCKNAME);
    }
    else
    { /* figlio, server */
        fd_skt = socket(AF_UNIX, SOCK_STREAM, 0);
        bind(fd_skt, (struct sockaddr *)&sa, sizeof(sa));

        listen(fd_skt, SOMAXCONN);
        pthread_t serverWorker[CLIENTS_NUM];
        sTh_t *argsServer = (sTh_t *)malloc(CLIENTS_NUM * sizeof(sTh_t));
        int workerCount = 0;

        while (workerCount < CLIENTS_NUM && (fd_c = accept(fd_skt, NULL, 0)) != -1)
        {
            argsServer[workerCount].id = workerCount;
            argsServer[workerCount].fdc = fd_c;
            pthread_create(&serverWorker[workerCount], NULL, serverWorkerTH, &argsServer[workerCount]);
            // printf("Opening th #%d\n", workerCount);
            workerCount++;
        }

        for (int i = 0; i < workerCount; i++)
        {
            pthread_join(serverWorker[i], NULL);
        }

        close(fd_skt);
        close(fd_c);
        unlink(SOCKNAME);
        // printf("Chiusura server\n");
        fflush(stdout);
        exit(EXIT_SUCCESS);
    }
    return 0;
}

void *clientTH(void *args)
{
    cTh_t *stru = (cTh_t *)args;
    // printf("Sono %d\n", stru->id);
    char *buff = (char *)malloc(256 * sizeof(char));
    int len = 0;
    int fd_skt = socket(AF_UNIX, SOCK_STREAM, 0);
    while (connect(fd_skt, (struct sockaddr *)&stru->sa, sizeof(stru->sa)) == -1)
    {
        if (errno == ENOENT)
            sleep(1); /* sock non esiste */
        else
            exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MSG_NUM; i++)
    {
        len = sprintf(buff, "|| id: %d - %s - #%d ||\n", stru->id, stru->msg, i);
        write(fd_skt, buff, len);
    }
    write(fd_skt, '\0', 1);

    return NULL;
}

void *serverWorkerTH(void *args)
{
    sTh_t *stru = (sTh_t *)args;
    char *buf = (char *)malloc(sizeof(char));
    char *resString = (char *)malloc(sizeof(char) * N);
    while (read(stru->fdc, buf, 1) != 0)
    {
        if (*buf == '\n')
        {
            printf("Server %d on FD: %d - got: %s\n", stru->id, stru->fdc, resString);
            free(resString);
            resString = (char *)malloc(sizeof(char) * N);
        }
        else
            strcat(resString, buf);
    }
    // printf("---- Server %d CHIUDO\n", stru->id);
    return NULL;
}