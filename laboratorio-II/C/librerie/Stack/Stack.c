#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

void print(Stack s){
  printf("Stack: ");
  while(s!=NULL){
    printf("%f -> ",s->v);
    s=s->next;
  }
  printf("NULL\n");
}


void push(Stack* s, double x){
  //creo un nodo nuovo
  Node* new= (Node*)malloc(sizeof(Node));
  if(new==NULL){
    printf("errore di malloc\n");
    exit(0);
  }
  new->v=x;

  //'leggo' il nodo alla lista corente
  new->next=*s;

  //aggiorno la testa
  *s=new;
}

double top(Stack s){
  if(s!=NULL)
    return s->v;
  printf("Non ci sono elementi da restituire.\n");
  return 0;
}

double pop(Stack* s){
  if (*s==NULL){
    printf("Non ci sono elementi da restituire.\n");
    return 0;
  }
  Node* temp=*s;
  double ris=temp->v;
  *s=(*s)->next;
  free(temp);
  
  return ris;
}

void freeS(Stack* s){

  while(*s!=NULL){
    Node* temp =*s;
    *s=(*s)->next;
    free(temp);
  }

}
