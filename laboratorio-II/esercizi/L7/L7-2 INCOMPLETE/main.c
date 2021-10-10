//https://drive.google.com/open?id=1AJnV3eMKF0MdnpgXJSG_2eTmAA9RE9Zs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 100

void scanString(char *);

int main(void)
{
    char s[DIM];

    scanf("%[^\n]s", &s);

    printf("%s\n", s);

    scanString(s);

    return 0;
}

void scanString(char *s)
{

    for (size_t i = 0; i < strlen(s); i++)
    {
        if (i == 0 || s[i - 1] == ' ')
        {
            if (strchr("aeiouyAEIOUY", s[i]) != 0)
            {
                printf("Parte con vocale\n");
            }
            else
            {
                printf("Parte con consonante\n");
            }
        }
    }
}