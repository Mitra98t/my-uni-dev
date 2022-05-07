#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void lsSort(void);

int main(int argc, char *argv[])
{
    lsSort();
    return 0;
}

void lsSort(void)
{
    int pfd[2]; // Descrittori di file
    pid_t pid1, pid2;

    if (pipe(pfd) == -1) // errore
        perror("pipe creation broke");

    switch (pid1 = fork()) //* figlio 1 che farà comando prima Pipe
    {
    case -1:
        // errore
        perror("fork1 broke");
        break;
    case 0:
        // figlio
        if (dup2(pfd[1], 1) == -1) // errore
            perror("dup2 broke");
        else
        {
            close(pfd[0]);
            close(pfd[1]);
            execlp("ls", "ls", (char *)NULL);
        }
        break;
    }
    switch (pid2 = fork()) //* figlio 2 che farà comando dopo Pipe
    {
    case -1:
        // errore
        perror("fork2 broke");
        break;
    case 0:
        // figlio
        if (dup2(pfd[0], 0) == -1) // errore
            perror("dup2 broke");
        else
        {
            close(pfd[0]);
            close(pfd[1]);
            execlp("sort", "sort", (char *)NULL);
        }
        break;
    }
    // padre
    close(pfd[0]);
    close(pfd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}