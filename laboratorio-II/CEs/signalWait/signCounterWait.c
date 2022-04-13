#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define EC(sc, m)           \
    if (sc == -1)           \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
    }

volatile int countINT = 0;
volatile int countTSTP = 0;
volatile int exitYes = 0;

void handlerINT();
void handlerTSTP();
void handlerALARM(int);

int main(int argc, char const *argv[])
{
    struct sigaction s;
    int sign;
    /*
    Devo rendere la zona di setup degli handler signalSafe
    */
    sigset_t set;

    EC(sigfillset(&set), "fillset");
    EC(pthread_sigmask(SIG_SETMASK, &set, NULL), "pthread_sigmask");

    EC(sigemptyset(&set), "emptyset");
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTSTP);
    sigaddset(&set, SIGALRM);

    while (1)
    {
        sigwait(&set, &sign);
        switch (sign)
        {
        case SIGINT:
            handlerINT();
            break;

        case SIGTSTP:
            handlerTSTP();
            break;
        case SIGALRM:
            break;
        }
    }

    while (1)
    {
        pause();
    }

    return 0;
}

void handlerINT()
{
    countINT++;
}

void handlerTSTP()
{
    char c;
    int r;
    printf("Ho ricevuto %d SIGINT\n", countINT); //! NOT SIGNAL SAFE

    countTSTP++;

    if (countTSTP >= 3)
    {
        write(1, "Usciamo? y/n\n", 13);

        exitYes = 1;
        alarm(10);

        while ((r = read(0, &c, sizeof(char))) == -1 && errno == EINTR)
        {
            write(1, "Usciamo? y/n\n", 13);
        }

        if (r == -1)
            _Exit(EXIT_FAILURE);

        if (c == 'y')
            _Exit(EXIT_SUCCESS);
        else
            exitYes = 0;
    }
}

void handlerALARM(int s)
{
    if (exitYes)
    {

        write(1, "ricevuto SIGALARM\n", 18);
        _Exit(EXIT_SUCCESS);
    }
}