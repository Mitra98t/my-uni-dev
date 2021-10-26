#include <stdio.h>

typedef enum
{
    s0,
    s1,
    s2,
    s3
} States;

States evalState(States cs, int input)
{
    switch (cs)
    {
    case s0:
        if (input == 1)
            return s1;
        return s0;
    case s1:
        if (input == 1)
            return s2;
        return s1;
    case s2:
        if (input == 1)
            return s3;
        return s2;
    case s3:
        if (input == 1)
            return s0;
        return s3;
    }
}
int printRes(States cs)
{
    switch (cs)
    {
    case s0:
        return 0;
    case s1:
        return 1;
    case s2:
        return 2;
    case s3:
        return 3;
    }
}

int main(void)
{
    States currState = s0;
    int x = 0;
    printf("STATO: %d\n", printRes(currState));
    while (1)
    {
        scanf("%d", &x);
        currState = evalState(currState, x);
        printf("STATO: %d\n", printRes(currState));
    }
    return 0;
}
