//https://drive.google.com/open?id=17eTg4MaPgM7Ml0qIGoY3-TxLcavSWFGw

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
    List l1 = NULL;
    List l2 = NULL;
    List l3 = NULL;
    int buff = 0;

    while (buff >= 0)
    {
        scanf("%d", &buff);
        if (buff >= 0)
            inserOrd(&l2, buff);
    }

    buff = 0;
    while (buff >= 0)
    {
        scanf("%d", &buff);
        if (buff >= 0)
            inserOrd(&l3, buff);
    }

    fusionOrd(&l1, l2, l3);

    print(l1);

    return 0;
}
