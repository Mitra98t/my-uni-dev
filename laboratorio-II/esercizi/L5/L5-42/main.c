//https://drive.google.com/open?id=15o3RVEOYQXQ2Uf3D14zgvIJ3NMfM_apw

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{

    int buff = 0;
    List l = NULL;

    do
    {
        scanf("%d", &buff);
        if (buff >= 0)
            addTail(&l, buff);
    } while (buff >= 0);

    int somma = calcoloSomma(l);
    printf("%d\n", somma);

    printf("%d\n", calcoloNElementi(l, somma));

    return 0;
}