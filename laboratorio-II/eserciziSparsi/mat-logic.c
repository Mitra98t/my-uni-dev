#include <stdio.h>
#include <stdbool.h>

#define R 4
#define C 3

int colMul3(int matrix[R][C]);

int main(void)
{
    int mat[R][C];

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            scanf("%d", &mat[i][j]);
        }
    }

    printf("%d\n", colMul3(mat));
}

int colMul3(int matrix[R][C])
{
    int res = -1;
    for (int j = 0; j < C; j++)
    {
        bool mul3 = true;
        for (int i = 0; i < R; i++)
        {
            if (matrix[i][j]%3 != 0){
                mul3 = false;
            }
        }
        if(mul3){
            res = j;
        }
    }
    return res;
}