//https://drive.google.com/open?id=1CsVEnh4WcJHuIJr3MDsxtHH5tGBCILqa

#include <stdio.h>
#include <stdlib.h>
#include "dynArr.h"

int main(void)
{
    int dim1, dim2 = 0;
    int buff = 0;
    DynArray a1;
    DynArray a2;
    DynArray a3;

    printf("Array A:\n");
    scanf("%d", &dim1);
    initDynArray(&a1, dim1);

    for (int i = 0; i < dim1; i++)
    {
        scanf("%d", &buff);
        pushDynArray(&a1, buff);
    }
    printDynArr(a1);

    printf("Array B:\n");
    scanf("%d", &dim2);
    initDynArray(&a2, dim2);

    for (int i = 0; i < dim2; i++)
    {
        scanf("%d", &buff);
        pushDynArray(&a2, buff);
    }
    printDynArr(a2);

    initDynArray(&a3, dim1 + dim2);
    fuseDynArrays(&a3, a1, a2);
    printf("Array risultato C\n");
    printDynArr(a3);
    printf("Ordinato: %d\n", isCresc(a3));

    return 0;
}
