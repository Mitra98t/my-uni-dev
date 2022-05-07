#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usa %s nomedire\n", argv[0]);
        exit(1);
    }

    const char *dirname = argv[1];

    struct stat statbuf;

    if (stat(dirname, &statbuf) == -1)
    {
        perror("stat");
        fprintf(stderr, "errore nella stat per il file %s\n", dirname);
        exit(1);
    }

    if (!S_ISDIR(statbuf.st_mode))
    {
        fprintf(stderr, "%s non è una directory\n", argv[1]);
        exit(1);
    }

    pid_t pid = fork();

    if (pid == 0)
    {
        // processo figlio
        execlp("/bin/ls", "ls", "-la", dirname, (char *)NULL);
        perror("execlp");
        exit(1);
    }
    // processo padre
    int status;
    if (waitpid(pid, &status, 0) == -1) // Aspetto in modo sincrono la fine del processo figlio.
    {
        perror("waitpid");
        exit(1);
    }

    if (WIFEXITED(status))
    {
        // terminato con una exit
        // posso leggere l'exit status
        fprintf(stdout, "processo figlio di pid %d terminato con exit(%d)\n", pid, WEXITSTATUS(status));
    }
    else
    {
        fprintf(stdout, "processo figlio di pid %d terminato non con exit\n", pid);
        // terminato NON con una exit ma magari con un segnale o per un exception con core dumped
        // posso usare funzioni specifiche per controllare se è stato terminato da cosa e con quale codici
    }

    return 0;
    // Potevo usare exit(0) ma exit termina il processo non la funzione
    // In questo caso return termina la funzione main che coincide col processo
    // Ma le due cose non sono equivalenti
}