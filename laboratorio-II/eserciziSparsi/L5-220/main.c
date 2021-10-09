//https://drive.google.com/open?id=171CYyHYxFwFzz-M9Zdho_O5H1UUf6M01

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
            inserOrd(&l, buff);
    }

    print(l);

    return 0;
}