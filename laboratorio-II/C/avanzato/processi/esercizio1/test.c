#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int status;
    pid = fork();
    if (pid == -1)
    {
        perror("Cannot fork");
        return -1;
    }
    if (pid)
    {
        // padre
        printf("%d padre pid - getpid %d\n", pid, getpid());
        pid = waitpid(pid, &status, 0);
        printf("Figlio finito\n");
        if (WIFEXITED(status))
        {
            /* il figlio terminato con exit o return */
            printf("stato % d\n", WEXITSTATUS(status));
        }
    }
    else
    {
        // figlio
        sleep(2);
        printf("%d figlio pid - getpid %d\n", pid, getpid());
        fflush(stdout);
        execl("/bin/ls", "ls", "-lah", (char *)NULL);
    }

    return 0;
}
