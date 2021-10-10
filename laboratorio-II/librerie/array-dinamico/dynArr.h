typedef struct
{
    int *array;
    size_t used;
    size_t size;
} DynArray;

void initDynArray(DynArray *, size_t);
void pushDynArray(DynArray *, int);
void freeDynArr(DynArray *);
void getInfoDynArr(DynArray *);
void sortDynArr(DynArray *arrP);
void printDynArr(DynArray);
int isCresc(DynArray);
void fuseDynArraysOrdered(DynArray*, DynArray, DynArray);
void fuseDynArrays(DynArray*, DynArray, DynArray);