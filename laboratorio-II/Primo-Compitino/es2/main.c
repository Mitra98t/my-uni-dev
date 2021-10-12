#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIM 15
#define SHIFT 4

char *encode(char *);
char *decode(char *);

int main(void)
{
    char s[DIM];
    scanf("%s", s);
    printf("%s è lunga: %ld", s, strlen(s));
    for (size_t i = 0; i < strlen(s); i++)
    {
        // printf("ASCII value of %c = %d", s[i], s[i]);
        if (s[i] >= 97)
            s[i] = s[i] - 32;
    }

    printf("\nEncode %s\n", encode(s));
    printf("\nDecode %s\n", decode(s));

    printf("\n%s\n", s);
    return 0;
}

char *encode(char *s)
{
    char *str = (char *)malloc((strlen(s) + 1) * sizeof(char));
    strcpy(str, s);

    for (size_t i = 0; i < strlen(str); i++)
    {

        str[i] = (((str[i] - 65) + (SHIFT )) % 26) + 65;
    }
    return str;
}

char *decode(char *s)
{
    char *str = (char *)malloc((strlen(s) + 1) * sizeof(char));
    strcpy(str, s);

    for (size_t i = 0; i < strlen(str); i++)
    {

        str[i] = (((str[i] - (SHIFT )) - 13) % 26) + 65;
    }
    return str;
}