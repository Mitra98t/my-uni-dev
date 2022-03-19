#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void func(void);

int main(int argc, char *argv[])
{
    func();
    return 0;
}

void func(void)
{

    int pfd[2][2];
    pid_t pid1, pid2, pid3;
    if (pipe(pfd[0]) == -1)
        perror("pipe1 creation broke");
    if (pipe(pfd[1]) == -1)
        perror("pipe2 creation broke");

    switch (pid1 = fork())
    {
    case -1:
        perror("fork 1");
        break;
    case 0:
        close(pfd[1][0]);
        close(pfd[1][1]);
        close(pfd[0][0]);
        if (dup2(pfd[0][1], 1) == -1)
            perror("dup2");
        else
        {
            execlp("ls", "ls", "-lah", (char *)NULL);
            close(pfd[0][1]);
        }
        break;
    }

    switch (pid2 = fork())
    {
    case -1:
        perror("fork 2");
        break;
    case 0:
        close(pfd[0][1]);
        close(pfd[1][0]);
        if ((dup2(pfd[0][0], 0) == -1) || (dup2(pfd[1][1], 1) == -1))
            perror("dup2");
        else
        {
            execlp("cut", "cut", "-d", " ", "-f", "1", (char *)NULL);
            close(pfd[0][0]);
            close(pfd[1][1]);
        }
        break;
    }

    switch (pid3 = fork())
    {
    case -1:
        perror("fork 2");
        break;
    case 0:
        close(pfd[0][0]);
        close(pfd[0][1]);
        close(pfd[1][1]);
        if (dup2(pfd[1][0], 0) == -1)
            perror("dup2");
        else
        {
            execlp("sort", "sort", (char *)NULL);
            close(pfd[1][0]);
        }
        break;
    }

    close(pfd[0][0]);
    close(pfd[0][1]);
    close(pfd[1][0]);
    close(pfd[1][1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);
}