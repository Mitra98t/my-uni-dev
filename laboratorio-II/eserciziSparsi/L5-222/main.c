//https://drive.google.com/open?id=17i_EypxTU5_HO5oP3LR10J1lsuQaAoMm

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
    List l1 = NULL;

    int buff = 0;

    while (buff >= 0)
    {
        scanf("%d", &buff);
        if (buff >= 0)
            inserOrdDecrescDup(&l1, buff);
    }

    fillOrdDecresc(l1);

    printInLine(l1);

    return 0;
}