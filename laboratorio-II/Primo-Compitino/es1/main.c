#include <stdio.h>

#define DIM 100

int main(void)
{
    int n = 0;
    int nums[DIM];
    scanf("%d", &n);

    for (size_t i = 0; i < n; i++)
    {
        scanf("%d", &nums[i]);
    }

    int res = 1;

    for (size_t i = 0; i < n; i++)
    {
        if (nums[i] % 2 == 0)
        {
            res *= nums[i];
        }
    }

    printf("%d\n", res);

    return 0;
}
