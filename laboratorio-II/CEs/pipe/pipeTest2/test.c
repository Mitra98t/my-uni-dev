#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
// #include <sys/stat.h>

void redirPipe(char *);

int main(int argc, char *argv[])
{
    redirPipe("questo lo scrivo in pippo");
    return 0;
}

void redirPipe(char *string)
{
    int fd;

    fd = open("pippo", O_WRONLY | O_TRUNC | O_CREAT, 0666);
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
        printf("%s\n", string);
    }
}