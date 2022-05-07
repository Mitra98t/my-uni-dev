#include <stdio.h>

//! DIVERSE VERSIONI SCRITTE SEMPRE PIU' PICCOLE.
// char myStrcopy(char *dest, const char *source)
// {
//     int i = 0;
//     while (source[i] != "\0")
//     {
//         dest[i] = source[i];
//         i++;
//     }
//     return dest;
// }

// char myStrcopy(char *dest, const char *source)
// {
//     while (*source)
//     {
//         I ++ sono l'ultima cosa che si valuta
//         *dest++ = *source++;
//     }
//     return dest;
// }

char myStrcopy(char *dest, const char *source)
{
    while ((*dest++ = *source++))
        ;
    return dest;
}

int main(void)
{
    char a[] = "ciao ciao";
    char b[10];
    myStrcopy(b, a);
    printf("A: %s\nB: %s", a, b);
}