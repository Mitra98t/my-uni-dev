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
#include <string.h>

#define IP "131.114.22.172" // server
// #define IP "10.101.34.121" // pcProf
// #define IP "127.0.0.1" //locale
#define PORT 7777
#define N 100

int main(int argc, char const *argv[])
{
    char buff[N];
    int sk, n;
    struct sockaddr_in server;

    fd_set fds, readFds;

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP);

    sk = socket(AF_INET, SOCK_STREAM, 0);

    if (connect(sk, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("connect");
        return EXIT_FAILURE;
    }

    FD_ZERO(&fds);
    FD_SET(sk, &fds);
    FD_SET(0, &fds);

    while (1)
    {
        readFds = fds;
        select(sk + 1, &readFds, NULL, NULL, NULL);

        if (FD_ISSET(0, &readFds))
        {
            n = read(0, buff, N);

            buff[n] = '\0';
            if (strcmp(buff, "exit\n") == 0)
                break;
            write(sk, buff, n);
        }

        if (FD_ISSET(sk, &readFds))
        {
            n = read(sk, buff, N);
            if (n > 0)
            {
                buff[n] = '\0';
                printf("---> %s\n", buff);
            }
            if (n == 0)
                break;
        }
    }

    close(sk);

    return 0;
}
