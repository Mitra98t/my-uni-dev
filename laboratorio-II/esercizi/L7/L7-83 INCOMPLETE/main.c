//https://drive.google.com/open?id=1DRW1h8slFk-isIFzCLXbk4iRVicqgaoY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 100

struct S
{
    char *txt;
    int length;
};
typedef struct S String;

int cmpfunc(const void *a, const void *b)
{
    String **s1 = (String **)a;
    String **s2 = (String **)b;

    return strcmp((*s1)->txt, (*s2)->txt);
}

int main(void)
{
    String *strs[DIM];
    int n = 0;
    char buff[DIM];

    scanf("%d\n", &n);

    for (size_t i = 0; i < n; i++)
    {
        strs[i] = (String *)malloc(sizeof(String));
        scanf("%s", &buff);
        strs[i]->length = strlen(buff);
        strs[i]->txt = (char *)malloc((strlen(buff) + 1) * sizeof(char));
        strcpy(strs[i]->txt, buff);
    }

    // for (size_t i = 0; i < n; i++)
    // {
    //     printf("%d\n", strs[i]->length);
    //     printf("%s\n", strs[i]->txt);
    // }

    qsort(strs, n, sizeof(String), cmpfunc);

    for (size_t i = 0; i < n; i++)
    {
        printf("%s\n", strs[i]->txt);
    }

    return 0;
}