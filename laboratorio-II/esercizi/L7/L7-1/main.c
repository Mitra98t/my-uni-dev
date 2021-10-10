//https://drive.google.com/open?id=1A2j5JaoznHZJHtw0z3wHxneLLS3Sv_6F

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 100

int isPalindrome(char *, int, int);

int main(void)
{
    char s1[DIM];
    char s2[DIM];
    char s3[DIM];

    char *strings[3] = {s1, s2, s3};

    for (size_t i = 0; i < 3; i++)
    {
        scanf("%s", strings[i]);
    }

    for (size_t i = 0; i < 3; i++)
    {
        printf("%s\n", isPalindrome(strings[i], 0, strlen(strings[i]) - 1) ? "palindrome" : "non palindrome");
    }

    return 0;
}

int isPalindrome(char *str, int s, int e)
{
    if (s == e)
        return 1;

    if (str[s] != str[e])
        return 0;

    if (s < e + 1)
        return isPalindrome(str, s + 1, e - 1);
    return 1;
}