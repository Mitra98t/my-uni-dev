#include <stdlib.h>
#include <stdio.h>
#include "List.h"

void freeListR(List *l)
{
  if (*l != NULL)
  {
    freeListR(&((*l)->next));
    free(*l);
    *l = NULL;
  }
}

void insertOrd(List *l, double x)
{
  Node *prev, *succ;
  prev = NULL;
  succ = *l;

  while (succ != NULL && succ->v < x)
  {
    //vado avanti al nodo succesivo
    prev = succ;
    succ = succ->next;
  }

  //creamo il nodo nuovo
  Node *new = (Node *)malloc(sizeof(Node));
  if (new == NULL)
  {
    printf("errore di malloc\n");
    exit(0);
  }
  new->v = x;

  //collego il nodo nuovo a succ e prec
  new->next = succ;

  if (prev != NULL) //inserisco all'interno della lista'
    prev->next = new;
  else //inserisco in testa
    *l = new;
}

void printList(List l)
{
  printf("List: ");
  while (l != NULL)
  {
    printf("%f -> ", l->v);
    l = l->next;
  }
  printf("NULL\n");
}

void insertOrdRec(List *l, double v)
{
  if ((*l) == NULL || (*l)->v > v)
  {
    //Insrtiento in testa
    Node *n = (Node *)malloc(sizeof(Node));
    n->v = v;
    n->next = (*l);
  }
  else
  {
    insertOrdRec(&((*l)->next), v);
  }
}