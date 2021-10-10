//https://drive.google.com/open?id=1BHbm92u1fl035xQOpi2sIhDDZWBXixSP

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
    List l = NULL;
    int buff = 0;

    while (buff >= 0)
    {
        scanf("%d", &buff);
        if (buff >= 0)
            addTail(&l, buff);
    }

    printf("%s", isStrtCresc(l) == 1 ? "True" : "False");

    return 0;
}