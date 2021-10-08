#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int removeValue(List*l, int v){
  if(*l == NULL)
    return -1;
  
  if((*l)->val == v){
    Node * tmp = (*l);
    (*l) = (*l)->next;
    free(tmp);
    return v;
  }

  Node * curr = (*l)->next;
  Node * prec = (*l);
  while(curr != NULL){
    if(curr->val == v){
      prec->next = curr->next;
      free(curr);
      return v;
    }
    curr = curr->next;
    prec = prec->next;
  }
  return -1;
}

int addHead(List *l, int v){
  if(v<0){
    return -1;
  }

  Node * newEl = (Node*)malloc(sizeof(Node));
  newEl->val = v;
  newEl->next = *l;
  *l = newEl;
  return newEl->val;
}

int addTail(List *l, int v){
  if(v<0){
    return -1;
  }

  Node * newEl = (Node*)malloc(sizeof(Node));
  newEl->val = v;
  newEl->next = NULL;

  if(*l == NULL){
    *l = newEl;
  }
  else{
    Node * curr = *l;
    while(curr->next != NULL){
      curr = curr->next;
    }
    curr->next = newEl;
  }
  return newEl->val;
}



void print(List l){
  while(l != NULL){
    printf("%d\n", l->val); //(*l).val
    l=l->next;
  }

  //printf("NULL\n");
}