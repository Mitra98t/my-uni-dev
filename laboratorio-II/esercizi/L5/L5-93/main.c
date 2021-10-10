//https://drive.google.com/open?id=15tHBomsvCNOBuiGd1OjGu2qhRqaripz_

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
    List l = NULL;
    int buff = 0;
    int n = 0;
    do
    {
        scanf("%d", &buff);
        if (buff >= 0)
        {
            addTail(&l, buff);
        }
    } while (buff >= 0);

    scanf("%d", &n);
    removeN(&l, n);

    print(l);

    return 0;
}