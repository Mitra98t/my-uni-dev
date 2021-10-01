#include <stdio.h>

#define NMAX 100

int main(void)
{
    int dim = 0;
    int a[NMAX];

    do
    {
        scanf("%d\n", &dim);
        if (dim > 100 || dim < 0)
        {
            printf("Inserisci un intero positivo compreso fra 1 e 100.\n");
        }
    } while (dim > 100 || dim < 0);

    for (int i = 0; i < dim; i++)
    {
        int dump;
        if (scanf("%d", &dump) != 2)
            printf("Inserisci un intero.\n");
        else
        {
            a[i] = dump;
        }
    }

    for (int i = 0; i < dim; i++)
    {
        if ((a[i] >= 0 && a[i] % 2 == 0) || (a[i] < 0 && a[i + 1] >= 0))
        {
            printf("%d\n", a[i]);
        }
    }

    return 0;
}