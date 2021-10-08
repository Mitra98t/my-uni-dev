#include <stdio.h>

int main()
{
    int x = 3;
    int *y = &x;

    printf("x\t %d\n", x);
    printf("&x\t %p\n", &x);
    printf("y\t %p\n", y);
    printf("&y\t %p\n", &y);
    printf("*y\t %d\n", *y);
}