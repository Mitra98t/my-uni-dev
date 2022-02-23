#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int pid;
    printf("Inizio\n");
    pid = fork();
    printf("%d: Ho ricevuto: %d\n", getpid(), pid);
    return 0;
}