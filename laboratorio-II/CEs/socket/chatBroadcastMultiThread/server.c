#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <errno.h>

// #define IP "10.101.34.121"
#define IP "127.0.0.1"
#define PORT 7777
#define N 100
#define W 5

typedef struct
{
    fd_set *workerSokets;
    fd_set *allClientSockets;
    int *maxAll, *maxWorker;
    pthread_mutex_t *workerMutex, *allMutex;
} wArg_t;

void worker(void *);

int main(int argc, char const *argv[])
{
    char buff[N];
    int sSk, client, n, maxS;
    struct sockaddr_in server;

    fd_set sockets, readSockets;

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP);

    sSk = socket(AF_INET, SOCK_STREAM, 0);
    bind(sSk, (struct sockaddr *)&server, sizeof(server));
    listen(sSk, SOMAXCONN);

    FD_ZERO(&sockets);
    FD_SET(sSk, &sockets);
    maxS = sSk;

    while (1)
    {
        readSockets = sockets;
        if (select(maxS + 1, &readSockets, NULL, NULL, NULL) == -1)
        {
            perror("select");
            continue;
        }
        fprintf(stderr, "disponibili: %d\n", n);
        //! ATTENZIONE SI DEVE ANDARE SULLA MAXS + 1
        for (int sd = 0; sd < maxS + 1; sd++)
        {
            if (FD_ISSET(sd, &readSockets))
            {
                if (sd == sSk)
                { //* server
                    client = accept(sSk, NULL, 0);
                    FD_SET(client, &sockets);
                    if (maxS < client)
                        maxS = client;
                }
                else
                { //* client
                    n = read(sd, buff, N);
                    if (n > 0)
                    {
                        buff[n] = '\0';
                        printf("Server ha ricevuto %s\n", buff);
                        for (client = 0; client <= maxS; client++)
                        {
                            if (client != sd && client != sSk)
                                write(sd, buff, n);
                        }
                    }
                    if (n == 0)
                    {
                        FD_CLR(sd, &sockets);
                        while (!FD_ISSET(maxS, &sockets))
                            maxS--;
                        close(sd);
                    }
                }
            }
        }
    }

    close(sSk);

    return 0;
}

void worker(void *args)
{
    // Riceve un fd_set da gestire per leggere
    // Riceve un fd_set di tutti i clienti connessi per scrivere

    fd_set *mySockets = ((wArg_t *)args)->workerSokets;
    fd_set *allSockets = ((wArg_t *)args)->allClientSockets;
    int *myMax = ((wArg_t *)args)->maxWorker;
    int *allMax = ((wArg_t *)args)->maxAll;
    pthread_mutex_t *myMutex = ((wArg_t *)args)->workerMutex;
    pthread_mutex_t *allMutex = ((wArg_t *)args)->allMutex;

    while (1)
    {
        pthread_mutex_lock(myMutex);
        fd_set readSockets = *mySockets;
        int readMax = *myMax;
        pthread_mutex_unlock(myMutex);
        if (select(readMax + 1, &readSockets, NULL, NULL, NULL) == -1)
        {
            perror("select");
            continue;
        }
        fprintf(stderr, "disponibili: %d\n", n);
        //! ATTENZIONE SI DEVE ANDARE SULLA MAXS + 1
        for (int sd = 0; sd < readMax + 1; sd++)
        {
            if (FD_ISSET(sd, &readSockets))
            {

                n = read(sd, buff, N);
                if (n > 0)
                {
                    buff[n] = '\0';
                    printf("Server ha ricevuto %s\n", buff);
                    pthread_mutex_lock(allMutex);
                    fd_set clients = *allSockets;
                    int cMax = *allMax;
                    pthread_mutex_unlock(allMutex);
                    for (int client = 0; client <= cMax; client++)
                    {
                        if (FD_ISSET(client, &clients) && client != sd)
                            write(sd, buff, n);
                    }
                }
                if (n == 0)
                {
                    pthread_mutex_lock(myMutex);
                    FD_CLR(sd, mySockets);
                    while (!FD_ISSET(*myMax, mySockets))
                        (*myMax)--;
                    pthread_mutex_unlock(myMutex);

                    pthread_mutex_lock(allMutex);
                    FD_CLR(sd, allSockets);
                    while (!FD_ISSET(*allMax, allSockets))
                        (*allMax)--;
                    pthread_mutex_unlock(allMutex);
                    close(sd);
                }
            }
        }
    }
}
}