#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("The quick brown fox jumped over");
    /* Il primo argomento di ogni programma (secondo parametro di execl)
        è il nome del programma chiamato */
    execl("/bin/echo", "echo", "the", "lazy", "dogs", (char *)NULL);
    /* se execl ritorna si è verificato un errore */
    perror("execl");
    return 1;
}

/*
il programma non stampa "The quick brown fox jumped over"
perché il buffer non viene flushato
*/