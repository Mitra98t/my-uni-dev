#include <stdio.h>
#include <stdlib.h>

struct N
{
    int val;
    struct N *next;
};
typedef struct N Node;
typedef Node *List;

int push(List *l, int v)
{
    if (v < 0)
    {
        return -1;
    }

    Node *newEl = (Node *)malloc(sizeof(Node));
    newEl->val = v;
    newEl->next = NULL;

    if (*l == NULL)
    {
        *l = newEl;
    }
    else
    {
        Node *curr = *l;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = newEl;
    }
    return newEl->val;
}

void freeListR(List *l)
{
    if (*l != NULL)
    {
        freeListR(&((*l)->next));
        free(*l);
        *l = NULL;
    }
}

int pop(List *l)
{
    if (*l == NULL)
    {
        return -1;
    }

    int res = (*l)->val;
    Node *tmp = *l;
    *l = (*l)->next;
    free(tmp);
    return res;
}

int peek(List *l)
{
    if (*l == NULL)
    {
        return -1;
    }

    return (*l)->val;
}

void printInLine(List l)
{
    while (l != NULL)
    {
        printf("%d ->", l->val);
        l = l->next;
    }
    printf("NULL\n");
}

int main(void)
{
    List l = NULL;
    int scelta = 0;
    int n = 0;
    // printf("POP %d\n", pop(&l));
    // printf("PEEK %d\n", peek(&l));

    // printInLine(l);

    // push(&l, 33);

    // printInLine(l);

    // push(&l, 66);

    // printInLine(l);

    // push(&l, 99);

    // printInLine(l);

    // printf("POP %d\n", pop(&l));
    // printInLine(l);

    // printf("PEEK %d\n", peek(&l));
    // printInLine(l);

    while (1)
    {
        printf("0: Crea una nuova coda vuota (cancellando eventualmente gli elementi esistenti)\n1: Push\n2: Pop\n3: Peek\n4: Stampa coda\n");
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 0:
            if (l != NULL)
                freeListR(&l);
            l = NULL;
            break;
        case 1:
            n = 0;
            printf("inserisci valore: ");
            scanf("%d\n", &n);
            push(&l, n);
        case 2:
            pop(&l);
        case 3:
            peek(&l);
        case 4:
            printInLine(l);

        default:
            printf("scelta non valida");
            break;
        }
    }

    return 0;
}