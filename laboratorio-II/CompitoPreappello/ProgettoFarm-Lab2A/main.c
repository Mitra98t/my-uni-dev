// #include <util.h>
// #include <errno.h>
// #include <dirent.h>
// #include <pthread.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <unistd.h>
// #include <semaphore.h>
// #include <sys/time.h>
// #include <ctype.h>
// #include <signal.h>

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

#include "boundedqueue.h"
#include "util.h"

#define EOJ_STR "<<EOJ"
#define SOCKNAME "./farm.sck"
#define UNIX_PATH_MAX 108
#define N 512

#define DEBUGG 0

#define printf_F(s) \
    if (DEBUGG)     \
        s;

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
    struct sockaddr_un sa;
} wTh_t;

typedef struct
{
    int fdc;
    int id;
} sTh_t;

typedef struct
{
    long val;
    char fName[255];
} data_t;

void *masterTH(void *);
void *workerTH(void *);
void *serverWorkerTH(void *);

void handlerGeneric();

volatile sig_atomic_t intGive = 0;

int main(int argc, char const *argv[])
{

    int fd_skt, fd_c;
    struct sockaddr_un sa;
    strncpy(sa.sun_path, SOCKNAME, UNIX_PATH_MAX);
    sa.sun_family = AF_UNIX;

    int n = 4;
    int q = 8;
    int t = 0;

    int R;

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

    printf_F(printf("VALORI n: %d - q: %d - t: %d\n", n, q, t));

    for (int i = 0; i < fileCount; i++)
    {
        printf_F(printf("lista file #%d - %s\n", i, files[i]));
    }

    pid_t pid;
    // int status;
    switch (pid = fork())
    {
    case -1:
        perror("cannot fork");
        break;
    case 0:
    {
        // PADRE

        struct sigaction s;

        sigset_t set;
        SYSCALL_EXIT(sigfillset, R, sigfillset(&set), "fillset");
        SYSCALL_EXIT(pthread_sigmask, R, pthread_sigmask(SIG_SETMASK, &set, NULL), "pthread_sigmask");

        SYSCALL_EXIT(sigemptyset, R, sigemptyset(&set), "emptyset");
        sigaddset(&set, SIGINT);

        // recupero il sigaction vecchio
        SYSCALL_EXIT(sigaction, R, sigaction(SIGINT, NULL, &s), "sigaction1");

        // lo modifico
        s.sa_mask = set;
        // applico coi sigaction i nuovi handler
        s.sa_handler = handlerGeneric;
        // SIGHUP, SIGINT, SIGQUIT, SIGTERM
        SYSCALL_EXIT(sigaction, R, sigaction(SIGHUP, &s, NULL), "sigaction3");
        SYSCALL_EXIT(sigaction, R, sigaction(SIGINT, &s, NULL), "sigaction2");
        SYSCALL_EXIT(sigaction, R, sigaction(SIGQUIT, &s, NULL), "sigaction3");
        SYSCALL_EXIT(sigaction, R, sigaction(SIGTERM, &s, NULL), "sigaction3");

        SYSCALL_EXIT(sigemptyset, R, sigemptyset(&set), "emptyset");
        SYSCALL_EXIT(pthread_sigmask, R, pthread_sigmask(SIG_SETMASK, &set, NULL), "pthread_sigmask");

        BQueue_t *queue = initBQueue(n);
        pthread_t masterThread;
        pthread_t workerThread[n];
        mTh_t *argMaster = (mTh_t *)malloc(sizeof(mTh_t));
        wTh_t *argWorkers = (wTh_t *)malloc(n * sizeof(wTh_t));

        for (int i = 0; i < n; i++)
        {
            argWorkers[i].q = queue;
            argWorkers[i].sa = sa;
        }

        argMaster->files = files;
        argMaster->filesCount = fileCount;
        argMaster->q = queue;
        argMaster->t = t;

        SYSCALL_EXIT(pthread_create, R, pthread_create(&masterThread, NULL, masterTH, argMaster), "Master Thread Creation");
        // pthread_create(&masterThread, NULL, masterTH, argMaster);

        for (int i = 0; i < n; i++)
        {
            SYSCALL_EXIT(pthread_create, R, pthread_create(&workerThread[i], NULL, workerTH, &argWorkers[i]), "Worker Thread Creation");
            // pthread_create(&workerThread[i], NULL, workerTH, &argWorkers[i]);
        }

        SYSCALL_EXIT(pthread_join, R, pthread_join(masterThread, NULL), "Join Thread Master");
        for (int i = 0; i < n; i++)
        {
            SYSCALL_EXIT(pthread_join, R, pthread_join(workerThread[i], NULL), "Join Thread Master");
        }

        SYSCALL_EXIT(unlink, R, unlink(SOCKNAME), "Unlink in Father");
        break;
    }
    default:
    {
        // FIGLIO

        sigset_t maskSig;
        sigfillset(&maskSig);
        pthread_sigmask(SIG_BLOCK, &maskSig, NULL);

        SYSCALL_EXIT(socket, R, fd_skt = socket(AF_UNIX, SOCK_STREAM, 0), "Socket Creaton");
        // fd_skt = socket(AF_UNIX, SOCK_STREAM, 0);
        SYSCALL_EXIT(bind, R, bind(fd_skt, (struct sockaddr *)&sa, sizeof(sa)), "Bind Socket");

        SYSCALL_EXIT(listen, R, listen(fd_skt, SOMAXCONN), "Listen on Socket");
        pthread_t serverWorker[n];
        sTh_t *argsServer = (sTh_t *)malloc(n * sizeof(sTh_t));
        int workerCount = 0;

        while (workerCount < n && (fd_c = accept(fd_skt, NULL, 0)) != -1)
        {
            argsServer[workerCount].id = workerCount;
            argsServer[workerCount].fdc = fd_c;
            SYSCALL_EXIT(pthread_create, R, pthread_create(&serverWorker[workerCount], NULL, serverWorkerTH, &argsServer[workerCount]), "Create Thread ServerWorker");
            printf_F(printf("Opening server worker th #%d\n", workerCount));
            workerCount++;
        }

        printf_F(printf("After opening server workers\n"));

        for (int i = 0; i < workerCount; i++)
        {
            SYSCALL_EXIT(pthread_join, R, pthread_join(serverWorker[i], NULL), "Join Thread ServerWorker");
        }

        SYSCALL_EXIT(close, R, close(fd_skt), "Close fd_skt");
        SYSCALL_EXIT(close, R, close(fd_c), "Close fd_c");
        // SYSCALL_EXIT(unlink, R, unlink(SOCKNAME), "Unlink Socket Figlio");
        // unlink(SOCKNAME);
        // exit(EXIT_SUCCESS);
        break;
    }
    }

    return 0;
}

void *masterTH(void *args)
{
    mTh_t *stru = (mTh_t *)args;

    for (int i = 0; i < stru->filesCount; i++)
    {
        if (access(stru->files[i], F_OK) == 0 && is_regular_file(stru->files[i]))
        {
            if (i)
                usleep(stru->t * 1000);
            push(stru->q, strdup(stru->files[i]));
            printf_F(printf("pushing file to queue: %s\n", stru->files[i]));
            if (intGive)
                break;
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

    int fd_skt, R;
    SYSCALL_EXIT(socket, R, fd_skt = socket(AF_UNIX, SOCK_STREAM, 0), "Socket in Thread Worker");

    while (connect(fd_skt, (struct sockaddr *)&stru->sa, sizeof(stru->sa)) == -1)
    {

        /*
        if (errno == 111 || errno == 2)
            ...
        else
            perror(...)
        */
        if (errno == ENOENT)
            sleep(1); /* sock non esiste */
        else
            exit(EXIT_FAILURE);
    }

    while ((filePath = pop(stru->q)) != NULL)
    {
        printf_F(printf("Read from queue: %s\n", filePath));
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
        data_t *toSend = (data_t *)malloc(sizeof(data_t));
        strcpy(toSend->fName, filePath);
        toSend->val = result;
        SYSCALL_EXIT(write, R, write(fd_skt, toSend, sizeof(data_t)), "Write to Socket");
        // write(fd_skt, "c\0", 2);
        printf_F(printf("write on soket - size %d\n", sizeof(data_t)));
        printf_F(printf("write on soket File: %s - Result: %ld\n", filePath, result));
        fclose(ptr);
    }

    push(stru->q, EOJ_STR);
    return NULL;
}

void *serverWorkerTH(void *args)
{
    sTh_t *stru = (sTh_t *)args;
    data_t *recived = (data_t *)malloc(sizeof(data_t));
    printf_F(printf("Inside server Worker %d\n", stru->id));
    int a = 0;
    while ((a = read(stru->fdc, recived, sizeof(data_t))) != 0)
    {
        printf_F(printf("valore a: %d - size %d\n", a, sizeof(data_t)));
        printf("--> %ld %s\n", recived->val, recived->fName);
    }
    return NULL;
}

void handlerGeneric()
{
    intGive = 1;
    printf("\n");
    fflush(stdout);
}

/*
clear && gcc -pthread -Wall -g boundedqueue.c main.c -o farm -I. -I utils/includes
*/