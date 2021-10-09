#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void add_end(ANONIMI *l, int mat)
{
    Stud *s = (Stud *)malloc(sizeof(Stud));
    s->mat = mat;
    s->next = NULL;
    if (*l == NULL)
    {
        *l = s;
    }
    else
    {
        Stud *curr = *l;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = s;
    }
}

int RecLength(ANONIMI l)
{
    if (l == NULL)
    {
        return 0;
    }
    if (l->next == NULL)
    {
        return 1;
    }

    return 1 + RecLength(l->next);
}

void RecStampaInversa(ANONIMI l)
{
    if (l == NULL)
        printf("");
    else
    {
        RecStampaInversa(l->next);
        printf("%d->", l->mat);
    }
}

void RecStampa(ANONIMI l)
{
    if (l == NULL)
        printf("NULL \n");
    else
    {
        printf("%d->", l->mat);
        RecStampa(l->next);
    }
}

void CancellaMultipli(ANONIMI *l, int n)
{
    if (*l == NULL)
        return;

    Stud *curr = (*l);
    Stud *prec = NULL;
    Stud *next = NULL;

    while (curr != NULL)
    {
        if (curr->mat % n == 0)
        {
            if (prec == NULL)
            {
                prec = curr;
                curr = curr->next;
                *l = curr;
                free(prec);
                prec = NULL;
            }
            else
            {
                next = curr->next;
                prec->next = curr->next;
                free(curr);
                curr = next;
            }
        }
        else
        {
            prec = curr;
            curr = curr->next;
        }
    }
}

int firstPari(ANONIMI l)
{
    while (l != NULL)
    {
        if (l->mat % 2 == 0)
            return l->mat;
        l = l->next;
    }
    return -1;
}

int firstDispari(ANONIMI l)
{
    while (l != NULL)
    {
        if (l->mat % 2 == 1)
            return l->mat;
        l = l->next;
    }
    return -1;
}