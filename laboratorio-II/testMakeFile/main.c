//https://drive.google.com/open?id=14JunMowkLHTv7au7cx0baP_5ztpJEF6b
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
    List l1 = NULL;
    List l2 = NULL;
    List l3 = NULL;
    int buff = 0;

    do
    {
        scanf("%d", &buff);
        if (buff >= 0)
            addTail(&l1, buff);
    } while (buff >= 0);

    do
    {
        scanf("%d", &buff);
        if (buff >= 0)
            addTail(&l2, buff);
    } while (buff >= 0);

    intersecOrd(l1, l2, &l3);

    print(l3);
    return 0;
}
