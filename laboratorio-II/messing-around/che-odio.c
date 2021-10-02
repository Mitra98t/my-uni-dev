#include <stdio.h>

void test(int *b);

int main(void)
{
    int b = 42;

    printf("\nSIZEOF INT: %d\n", sizeof(int));
    printf("\nINDEX: %p\n", &b);
    printf("\nVALUE: %d\n", b);

    // printf("\nSENZA &\n");
    // test(b);
    printf("\nCON &\n");
    test(&b);

    return 0;
}

void test(int *b)
{
    for (int i = 0; i < 10; i++)
    {
        printf("INDEX: %d\n", &b[i]);
        printf("VALUE: %d\n", b[i]);
    }
}