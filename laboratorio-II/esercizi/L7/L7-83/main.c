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

    if (strcmp(s1.txt, s2.txt) > 0)
        return 0;
    else if (s1.length == s2.length)
        return s1.length<s2.length> 0 ? 0 : 1;
    else
        return 1;
}

int main(void)
{
    int n = 0;
    char buff[DIM];

    scanf("%d\n", &n);

    String *strs = calloc(n, sizeof(String));

    for (size_t i = 0; i < n; i++)
    {
        strs[i] = *(String *)malloc(sizeof(String));
        scanf("%s", buff);
        strs[i].length = strlen(buff);
        strs[i].txt = (char *)malloc((strlen(buff) + 1) * sizeof(char));
        strcpy(strs[i].txt, buff);
    }

    qsort(strs, n, sizeof(String), cmpfunc);

    for (size_t i = 0; i < n; i++)
    {
        printf("%s\n", strs[i].txt);
    }

    return 0;
}