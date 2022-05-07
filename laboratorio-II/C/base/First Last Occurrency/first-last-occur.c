//https://drive.google.com/open?id=12zKXmcJWk3iKLv683IbjsZD_vL7p6Nbs

#include <stdio.h>

#define DIM 7

void primoultimopari(int[], int *, int *);

int main(void)
{
    int nums[DIM];
    int first = -1;
    int last = -1;

    for (int i = 0; i < DIM; i++)
    {
        if (scanf("%d", &nums[i]) != 1)
        {
            scanf("%*[^\n]\n");
            i--;
        }
    }

    primoultimopari(nums, &first, &last);

    printf("%d %d\n", first, last);
}

void primoultimopari(int arr[], int *first, int *last)
{
    for (int i = 0; i < DIM; i++)
    {
        if (arr[i] % 2 == 0)
        {
            *last = i;
            if (*first == -1)
                *first = i;
        }
    }
}