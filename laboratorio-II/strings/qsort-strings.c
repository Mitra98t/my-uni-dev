#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stringCmp(const void *s1, const void *s2);
int stringCmpLessGraf(const void *s1, const void *s2);

int main(void)
{

    char *a[5] = {"ciao", "va", "come", "Hasjdn2", "123123"};

    qsort(a, 5, sizeof(char *), stringCmp);

    printf("\nOrdinamento normale:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", a[i]);
    }

    qsort(a, 5, sizeof(char *), stringCmpLessGraf);

    printf("\nOrdinamento lessico-grafico:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", a[i]);
    }

    return 0;
}

int stringCmp(const void *s1, const void *s2)
{
    char **ss1 = (char **)s1;
    char **ss2 = (char **)s2;
    return strcmp(*ss1, *ss2);
}

int stringCmpLessGraf(const void *s1, const void *s2)
{
    char **ss1 = (char **)s1;
    char **ss2 = (char **)s2;
    //! NOTA IL -
    return -strcmp(*ss1, *ss2);
}