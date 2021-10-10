#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int addTail(List *l, int v)
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

void insertOrd(List *l, int v)
{
    if ((*l) == NULL)
    {
        Node *newN = (Node *)malloc(sizeof(Node));
        newN->val = v;
        newN->next = NULL;
        (*l) = newN;
    }
    else if (v < (*l)->val)
    {
        Node *newN = (Node *)malloc(sizeof(Node));
        newN->val = v;
        newN->next = *l;
        *l = newN;
    }
    else
    {
        Node *curr = *l;
        while (curr != NULL)
        {
            if (curr->val < v && curr->next == NULL)
            {
                Node *newN = (Node *)malloc(sizeof(Node));
                newN->val = v;
                newN->next = NULL;
                curr->next = newN;
            }
            else if (curr->val < v && curr->next->val > v)
            {
                Node *newN = (Node *)malloc(sizeof(Node));
                newN->val = v;
                newN->next = curr->next;
                curr->next = newN;
            }
            curr = curr->next;
        }
    }
}

int produttoriaInRange(List l, int n, int m)
{
    int prod = 1;

    if (l == NULL)
        return -1;

    while (l != NULL)
    {
        if (l->val > n && l->val < m)
            prod *= l->val;

        l = l->next;
    }
    return prod;
}

void print(List l)
{
    while (l != NULL)
    {
        printf("%d\n", l->val);
        l = l->next;
    }
}
