//https://drive.google.com/open?id=1DemCEC4eSIT3UEE7gAfDOsa6e1MmmHCj

#include <stdlib.h>
#include <stdio.h>
#include "dynArr.h"

#define DIM 100

int cmpfuncPari(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
int cmpfuncDisp(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

int main(void)
{
    DynArray arrFinal;
    DynArray aP;
    DynArray aD;

    int n, buff = 0;

    scanf("%d", &n);

    initDynArray(&arrFinal, n);
    initDynArray(&aP, n / 2);
    initDynArray(&aD, n / 2);

    for (size_t i = 0; i < n; i++)
    {
        scanf("%d", &buff);
        if (buff % 2 == 0)
        {
            pushDynArray(&aP, buff);
        }
        else
        {
            pushDynArray(&aD, buff);
        }
    }

    qsort(aP.array, aP.used, sizeof(int), cmpfuncPari);
    qsort(aD.array, aD.used, sizeof(int), cmpfuncDisp);

    fuseDynArrays(&arrFinal, aP, aD);

    // for (size_t i = 0; i < n; i++)
    // {
    //     printf("%d\n", arrFinal[i]);
    // }

    printBRDynArr(arrFinal);

    return 0;
}