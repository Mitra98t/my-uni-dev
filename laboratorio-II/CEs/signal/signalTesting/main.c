#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

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

#define EC(sc, m)           \
    if (sc == -1)           \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    }

void *belTH(void *);

void handlerGeneric(int);

volatile sig_atomic_t intGive = 0;

int main(int argc, char const *argv[])
{
    struct sigaction s;

    sigset_t set;
    EC(sigfillset(&set), "fillset");
    EC(pthread_sigmask(SIG_SETMASK, &set, NULL), "pthread_sigmask");

    EC(sigemptyset(&set), "emptyset");
    sigaddset(&set, SIGINT);

    // recupero il sigaction vecchio
    EC(sigaction(SIGINT, NULL, &s), "sigaction1");


    // lo modifico
    s.sa_mask = set;
    // applico coi sigaction i nuovi handler
    s.sa_handler = handlerGeneric;
    EC(sigaction(SIGINT, &s, NULL), "sigaction2");

    s.sa_handler = handlerGeneric;
    EC(sigaction(SIGTSTP, &s, NULL), "sigaction3");

    EC(sigemptyset(&set), "emptyset");
    EC(pthread_sigmask(SIG_SETMASK, &set, NULL), "pthread_sigmask");

    pthread_t threadBello;
    EC(pthread_create(&threadBello, NULL, belTH, NULL), "creazione thread bello");

    EC(pthread_join(threadBello, NULL), "join thread");
    printf("simone bello\n");

    return 0;
}

void *belTH(void *args)
{
    for (int i = 0; i < 4; i++)
    {
        if (intGive)
            break;
        printf("Angelo Licco %d\n", i);
        sleep(2);
    }
    return NULL;
}

void handlerGeneric(int s)
{
    printf("ah ah ah int\n");
    intGive = 1;
}
