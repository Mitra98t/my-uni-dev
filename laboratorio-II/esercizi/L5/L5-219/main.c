//https://drive.google.com/open?id=16bANy86Q0MZyFlqFnugB2b3O0NwELGch

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
    int n, m, buff = 0;
    List l = NULL;

    scanf("%d", &n);
    scanf("%d", &m);

    do
    {
        scanf("%d", &buff);
        if (buff >= 0)
            insertOrd(&l, buff);
    } while (buff >= 0);

    printf("%d\n", produttoriaInRange(l, n, m));

    return 0;
}