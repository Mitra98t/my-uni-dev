#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
// #include <sys/stat.h>

void lsToFile(char *);

int main(int argc, char *argv[])
{
    lsToFile("pippo.txt");
    return 0;
}

void lsToFile(char *pathToFile)
{
    int pfd[2];
    pid_t pid1, pid2;
    int fd;

    if (pipe(pfd) == -1)
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

    switch (pid2 = fork()) //* figlio 1 che farà comando prima Pipe
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
            fd = open(pathToFile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
            /*
             * Duplica FD su STDOUT
             * Per questo metto fd su 1
             * 1 è stdout
             */
            if (dup2(fd, 1) == -1)
                perror("dup2 broke");
            else
            {
                close(fd); // non mi serve più quello vecchio ora che lo ho copiato su 1
                close(pfd[0]);
                close(pfd[1]);
                // Stampo in out qualcosa che viene inserito nel fd di pippo.txt
                printf("Numero di elementi in ls\n\n");
                // fflush di stdout perche altrimenti exec lo ignora
                fflush(stdout);
                // eseguo l'exec quindi stampo ls in pippo.txt
                execlp("wc", "wc", "-l", (char *)NULL);
            }
        }
        break;
    }
    // padre
    close(pfd[0]);
    close(pfd[1]);
    waitpid(pid1, NULL, 0);
    printf("Done\n");
}