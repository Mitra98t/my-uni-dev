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
    String s1 = *((String *)a);
    String s2 = *((String *)b);

    printf("Start\nS1: %s Length: %d\nS2: %s Length: %d\n", (s1.txt), s1.length, s2.txt, s2.length);
    if (strcmp(s1.txt, s2.txt) > 0)
    {
        if (s1.length > s2.length)
        {
            printf("End s1 > s2\n");
            return 1;
        }
        else
        {
            printf("End s1 < s2\n");
            return -1;
        }
    }
    else
    {
        printf("End lessicografico\n");
        return strcmp(s1.txt, s2.txt);
    }
}

int main(void)
{
    String **strs[DIM];
    int n = 0;
    char buff[DIM];

    scanf("%d\n", &n);

    for (size_t i = 0; i < n; i++)
    {
        (*strs)[i] = malloc(sizeof(String));
        scanf("%s", &buff);
        (*strs)[i]->length = strlen(buff);
        (*strs)[i]->txt = (char *)malloc((strlen(buff) + 1) * sizeof(char));
        strcpy((*strs)[i]->txt, buff);
    }

    for (size_t i = 0; i < n; i++)
    {
        printf("%d\n", (*strs)[i]->length);
        printf("%s\n", (*strs)[i]->txt);
    }

    qsort(strs, n, sizeof(String), cmpfunc);

    for (size_t i = 0; i < n; i++)
    {
        printf("%s\n", (*strs)[i]->txt);
    }

    return 0;
}