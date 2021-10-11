#include <stdio.h>
#include <stdlib.h>

#define DIM 100

int distanza(float x1, float y1, float x2, float y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}


int main(void)
{
    float arr[DIM][2];
    float x, y = 0.0;
    int n = 0;
    scanf("%d", &n);

    // for (size_t i = 0; i < n; i++)
    // {
    //     printf("x: %d -- y: %d", coords[i]->x, coords[i]->y);
    // }

    for (size_t i = 0; i < n; i++)
    {
        scanf("%f %f", &x, &y);
        arr[i][0] = x;
        arr[i][1] = y;
        // coords[i] = newC;
    }

    for (size_t i = 0; i < n; i++)
    {
        // printf("%d", distanza(xarr[i], yarr[i], x, y));
        if (distanza(arr[i][0], arr[i][1], x, y) > 3)
            printf("%.2f %.2f\n", arr[i][0], arr[i][1]);
    }
    return 0;
}