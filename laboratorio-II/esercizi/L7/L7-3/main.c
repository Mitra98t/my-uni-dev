/*
Scrivere un programma che legge da standard input un numero di righe r e un numero di colonne c, 
e poi gli elementi di una matrice rXc. Il programma deve ordinare le righe de la matrice 
in ordine crescente in base agli elementi sulla prima colonna. 
Se gli elementi sono uguali, si ordina in base alla seconda colonna, poi terza colonna, etc.
Il programma stampa la matrice con le righe ordinate (vedi test case per esempi).
*/

#include <stdio.h>
#include <stdlib.h>

#define DIM 100

void printMatrix(int *[], int, int);
void orderCol(int *[], int, int);

int main(void)
{
    int *rows[DIM];
    int buffer[DIM];
    int r, c = 0;

    scanf("%d\n", &r);
    scanf("%d\n", &c);

    for (size_t i = 0; i < r; i++)
    {
        rows[i] = malloc(c * sizeof(int));
        for (size_t j = 0; j < c; j++)
        {
            scanf("%d", &rows[i][j]);
        }
    }

    for (int i = c - 1; i >= 0; i--)
    {
        orderCol(rows, r, i);
    }

    printMatrix(rows, r, c);

    return 0;
}

void printMatrix(int *mat[], int r, int c)
{
    for (size_t i = 0; i < r; i++)
    {
        for (size_t j = 0; j < c; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void orderCol(int *mat[], int dim, int col)
{
    for (size_t i = 0; i < dim; i++)
    {
        for (size_t j = 0; j < dim - 1; j++)
        {
            if (mat[j][col] > mat[j + 1][col])
            {
                int *tmp = mat[j + 1];
                mat[j + 1] = mat[j];
                mat[j] = tmp;
            }
        }
    }
}