#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DIM 15

int main(void)
{
    char *s[DIM];
    scanf("%s", &s);

    for (size_t i = 0; i < strlen(*s); i++)
    {
        printf("ASCII value of %c = %d", s[i], s[i]);
    }

    // printf("\n%s\n", res);


    return 0;
}