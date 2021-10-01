#include <stdio.h>

int main(void)
{
    int dim = 0;
    printf("Inserisci dimensione \n");
    scanf("%d", &dim);

    int aMat[dim][dim], bMat[dim][dim], resMat[dim][dim];

    printf("Inserisci prima matrice \n");
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            scanf("%d", &aMat[i][j]);
        }
    }

    printf("Inserisci seconda matrice \n");
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            scanf("%d", &bMat[i][j]);
        }
    }

    printf("Risultato matrice \n");
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            resMat[i][j] = 0;
            for (int k = 0; k < dim; k++)
            {
                resMat[i][j] += aMat[i][k] * bMat[k][j];
            }
            printf("%d ", resMat[i][j]);
        }
            printf("\n");
    }

    return 0;
}