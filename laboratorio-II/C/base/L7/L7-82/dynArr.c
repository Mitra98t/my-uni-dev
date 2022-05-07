#include <stdio.h>
#include <stdlib.h>
#include "dynArr.h"

void initDynArray(DynArray *arrP, size_t initSize)
{
    arrP->array = malloc(initSize * sizeof(int));
    arrP->used = 0;
    arrP->size = initSize;
}

void pushDynArray(DynArray *arrP, int val)
{
    if (arrP->used == arrP->size)
    {
        arrP->size *= 2;
        arrP->array = realloc(arrP->array, arrP->size * sizeof(int));
    }
    arrP->array[arrP->used++] = val;
}

void freeDynArr(DynArray *arrP)
{
    free(arrP->array);
    arrP->array = NULL;
    arrP->used = arrP->size = 0;
}

void getInfoDynArr(DynArray *arrP)
{
    printf("\nIndex: %p\n", arrP->array);
    printf("Used: %zu\n", arrP->used);
    printf("Size: %zu\n", arrP->size);
}

void sortDynArr(DynArray *arrP)
{
    int i, j, temp;
    for (i = 0; i < arrP->used; i++)
    {
        for (j = 0; j < arrP->used; j++)
        {
            if (arrP->array[i] < arrP->array[j])
            { //use getter than (>) symbol for sorting from getter than to less than

                temp = arrP->array[i];
                arrP->array[i] = arrP->array[j];
                arrP->array[j] = temp;
            }
        }
    }
}

void fuseDynArrays(DynArray *aR, DynArray a1, DynArray a2)
{
    for (int i = 0; i < a1.used; i++)
    {
        pushDynArray(aR, a1.array[i]);
    }
    for (int i = 0; i < a2.used; i++)
    {
        pushDynArray(aR, a2.array[i]);
    }
}

void ordFuseDynArrays(DynArray *aR, DynArray a1, DynArray a2)
{
    for (int i = 0; i < a1.used; i++)
    {
        pushDynArray(aR, a1.array[i]);
    }
    for (int i = 0; i < a2.used; i++)
    {
        pushDynArray(aR, a2.array[i]);
    }

    sortDynArr(aR);
}

int isCresc(DynArray a)
{
    for (int i = 0; i < a.used - 1; i++)
    {
        if (a.array[i] > a.array[i + 1])
            return 0;
    }
    return 1;
}

void printDynArr(DynArray arrP)
{
    for (int i = 0; i < arrP.used; i++)
    {
        printf("%d ", arrP.array[i]);
    }
    printf("\n");
}

void printBRDynArr(DynArray arrP)
{
    for (int i = 0; i < arrP.used; i++)
    {
        printf("%d\n", arrP.array[i]);
    }
}