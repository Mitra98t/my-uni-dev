#include <stdio.h>

#define N 10

int a;

int main(int argc, char const *argv[])
{
    int b = 0;
    scanf("%d\n", &a);
    scanf("%d", &b);

    printf("SOMMA: %d\n%d\n", (a + b), N);

    return 0;
}
