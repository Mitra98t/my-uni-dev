#include <stdio.h>
#include <string.h>

#define DIM 3

char checkRowWin(char mat[DIM][DIM])
{
    char rowEl;
    int rowWin = 0;
    for (int i = 0; i < DIM; i++)
    {
        rowEl = mat[i][0];
        rowWin = 1;
        for (int j = 0; j < DIM; j++)
        {
            if (mat[i][j] != rowEl || mat[i][j] == '-')
                rowWin = 0;
        }
        if (rowWin)
            return rowEl;
    }
    return '-';
}

char checkColWin(char mat[DIM][DIM])
{
    char colEl;
    int colWin = 0;
    for (int i = 0; i < DIM; i++)
    {
        colEl = mat[0][i];
        colWin = 1;
        for (int j = 0; j < DIM; j++)
        {
            if (mat[j][i] != colEl || mat[j][i] == '-')
                colWin = 0;
        }
        if (colWin)
            return colEl;
    }
    return '-';
}

char checkDiagWin(char mat[DIM][DIM])
{
    int fstDWin = 1;
    int sndDWin = 1;
    char fstDEl = mat[0][0];
    char sndDEl = mat[0][2];
    for (int i = 1; i < DIM; i++)
    {
        if (mat[i][i] != fstDEl)
        {
            fstDWin = 0;
        }
        if (mat[i][2 - i] != sndDEl)
        {
            sndDWin = 0;
        }
    }
    if (fstDWin)
        return fstDEl;
    if (sndDWin)
        return sndDEl;
    return '-';
}

int main(void)
{
    char mat[DIM][DIM];

    // for (int i = 0; i < DIM; i++)
    // {
    //     scanf("%c %c %c", &mat[i][0], &mat[i][1], &mat[i][2]);
    // }

    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            scanf("%s", &mat[i][j]);
        }
    }

    char vincitore = (checkRowWin(mat) == '-' ? (checkColWin(mat) == '-' ? checkDiagWin(mat) : checkColWin(mat)) : checkRowWin(mat));
    if (vincitore == '-')
    {
        printf("pareggio\n");
    }
    else
    {
        printf("vince %c\n", vincitore);
    }
}