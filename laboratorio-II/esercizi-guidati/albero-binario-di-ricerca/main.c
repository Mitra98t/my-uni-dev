#include <stdio.h>
#include <stdlib.h>

struct N
{
    int val;
    struct N *sx;
    struct N *dx;
};
typedef struct N Node;
typedef Node *Tree;

void insertNode(Tree *, int);
void printTree(Tree);

int main(void)
{
    Tree albero = NULL;
    int n = 0;

    while (n >= 0)
    {
        scanf("%d", &n);
        insertNode(&albero, n);
    }

    printTree(albero);
    return 0;
}

void insertNode(Tree *radice, int v)
{
    if (*radice == NULL)
    {
        Node *tmp = (Node *)malloc(sizeof(Node));
        tmp->val = v;
        tmp->sx = NULL;
        tmp->dx = NULL;
        *radice = tmp;
    }
    else
    {
        if ((*radice)->val > v) //vai a sx
        {
            insertNode(&(*radice)->sx, v);
        }
        else if ((*radice)->val <= v) //vai a dx
        {
            insertNode(&(*radice)->dx, v);
        }
    }
}

void printTree(Tree radice)
{
    if (radice->sx != NULL)
    {
        printTree(radice->sx);
    }
    printf("%d\n", radice->val);
    if (radice->dx != NULL)
    {
        printTree(radice->dx);
    }
}