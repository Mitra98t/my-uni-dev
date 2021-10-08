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

void intersecOrd(List l1, List l2, List *l3)
{
    printf("started intersection\n");
    Node *l2Start = l2;
    while (l1 != NULL)
    {
        l2 = l2Start;
        while (l2 != NULL)
        {
            if (l1->val == l2->val)
            {
                printf("Equal in %d\n", l1->val);
                insertOrd(l3, l1->val);
            }
            l2 = l2->next;
        }
        l1 = l1->next;
    }
}

void insertOrd(List *l3, int v)
{
    if ((*l3) == NULL)
    {
        Node *newN = (Node *)malloc(sizeof(Node));
        newN->val = v;
        newN->next = NULL;
        (*l3) = newN;
    }
    else if (v < (*l3)->val)
    {
        Node *newN = (Node *)malloc(sizeof(Node));
        newN->val = v;
        newN->next = *l3;
        *l3 = newN;
    }
    else
    {
        Node *curr = *l3;
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

void print(List l)
{
    while (l != NULL)
    {
        printf("%d\n", l->val);
        l = l->next;
    }
}
