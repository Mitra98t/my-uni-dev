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
#define SOCKNAME "./mysock"
#define N 100

int main(void)
{
    int fd_skt, fd_c;
    char buf[N];
    struct sockaddr_un sa;
    strncpy(sa.sun_path, SOCKNAME, UNIX_PATH_MAX);
    sa.sun_family = AF_UNIX;
    if (fork() != 0)
    { /* padre, server */
        fd_skt = socket(AF_UNIX, SOCK_STREAM, 0);
        bind(fd_skt, (struct sockaddr *)&sa, sizeof(sa));
        listen(fd_skt, SOMAXCONN);
        fd_c = accept(fd_skt, NULL, 0);
        read(fd_c, buf, N);
        printf("Server got: %s\n", buf);
        write(fd_c, "Bye !", 5);
        close(fd_skt);
        close(fd_c);
        unlink(SOCKNAME);
        exit(0);
    }
    else
    { /* figlio, client */
        fd_skt = socket(AF_UNIX, SOCK_STREAM, 0);
        while (connect(fd_skt, (struct sockaddr *)&sa, sizeof(sa)) == -1)
        {
            if (errno == ENOENT)
                sleep(1); /* sock non esiste */
            else
                exit(1);
        }

        write(fd_skt, "Hallo !", 7);
        read(fd_skt, buf, N);
        printf("Client got: %s\n", buf);
        close(fd_skt);
        exit(0);
    }
    return 0;
}
