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

void inserOrdCrescDup(List *l, int v)
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

void inserOrdDecrescDup(List *l, int v)
{
  if (*l == NULL || v >= (*l)->val)
  {
    Node *n = (Node *)malloc(sizeof(Node));
    n->val = v;
    n->next = *l;
    *l = n;
  }

  Node *curr = *l;
  while (curr != NULL)
  {
    if (v < curr->val)
    {
      if (curr->next == NULL)
      {
        Node *n = (Node *)malloc(sizeof(Node));
        n->val = v;
        n->next = NULL;
        curr->next = n;
      }
      else if (v >= curr->next->val)
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

void fillOrdDecresc(List l)
{
  if (l == NULL)
    return;
  while (l->next != NULL)
  {
    if (l->val - 1 != l->next->val && l->val != l->next->val)
    {
      Node *n = (Node *)malloc(sizeof(Node));
      n->val = l->val - 1;
      n->next = l->next;
      l->next = n;
    }
    l = l->next;
  }
}

void printBR(List l)
{
  while (l != NULL)
  {
    printf("%d\n", l->val); //(*l).val
    l = l->next;
  }
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

void freeListR(List *l)
{
  if (*l != NULL)
  {
    freeListR(&((*l)->next));
    free(*l);
    *l = NULL;
  }
}
