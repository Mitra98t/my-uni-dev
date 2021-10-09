#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void inserOrd(List *l, int v)
{
    if (*l == NULL || v <= (*l)->val)
    {
        Node *n = (Node *)malloc(sizeof(Node));
        n->val = v;
        n->next = *l;
        *l = n;
    }

    Node *curr = *l;
    while (curr != NULL)
    {
        if (v > curr->val)
        {
            if (curr->next == NULL)
            {
                Node *n = (Node *)malloc(sizeof(Node));
                n->val = v;
                n->next = NULL;
                curr->next = n;
            }
            else if (v <= curr->next->val)
            {
                Node *n = (Node *)malloc(sizeof(Node));
                n->val = v;
                n->next = curr->next;
                curr->next = n;
            }
        }
        curr = curr->next;
    }
}

void print(List l)
{
    while (l != NULL)
    {
        printf("%d -> ", l->val);
        l = l->next;
    }
    printf("NULL\n");
}