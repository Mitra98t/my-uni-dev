#include <stdio.h>
#include <string.h>

int compare(const void *a, const void *b)
{
    const char *ia = *(const char **)a;
    const char *ib = *(const char **)b;

    int l1 = strlen(a);
    int l2 = strlen(b);

    if (l1 < l2)
        return -1;
    if (l1 > l2)
        return 1;
    return strcmp(ia, ib);
}

int main(void)
{

    return 0;
}