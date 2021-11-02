#include <stdio.h>

int palindrome();

int main(void)
{
    printf("%d\n", palindrome());
    return 0;
}

int palindrome()
{
    char c1, c2;
    int res;
    scanf("%c", &c1);
    if (c1 == '*')
    {
        return 1;
    }
    else
    {
        res = palindrome();
        scanf("%c", &c2);
        if (c1 != c2)
            return 0;
        else
            return res;
    }
}