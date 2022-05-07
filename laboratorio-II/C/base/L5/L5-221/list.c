#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int removeValue(List *l, int v)
{
  if (*l == NULL)
    return -1;

  if ((*l)->val == v)
  {
    Node *tmp = (*l);
    (*l) = (*l)->next;
    free(tmp);
    return v;
  }

  Node *curr = (*l)->next;
  Node *prec = (*l);
  while (curr != NULL)
  {
    if (curr->val == v)
    {
      prec->next = curr->next;
      free(curr);
      return v;
    }
    curr = curr->next;
    prec = prec->next;
  }
  return -1;
}

int addHead(List *l, int v)
{
  if (v < 0)
  {
    return -1;
  }

  Node *newEl = (Node *)malloc(sizeof(Node));
  newEl->val = v;
  newEl->next = *l;
  *l = newEl;
  return newEl->val;
}

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

void fusionOrd(List *l1, List l2, List l3)
{
  while (l2 != NULL)
  {
    inserOrd(l1, l2->val);
    l2 = l2->next;
  }
  while (l3 != NULL)
  {
    inserOrd(l1, l3->val);
    l3 = l3->next;
  }
}

void print(List l)
{
  while (l != NULL)
  {
    printf("%d --> ", l->val); //(*l).val
    l = l->next;
  }
  printf("NULL\n");
}