#include "stack.h"
#include <stdio.h>

void push (int v, Stack* s){
  s->elements[s->n]=v;
  s->n++;
}

int pop (Stack* s){
  int e=s->elements[s->n-1];
  s->n--;
  return e;
}

int top (Stack s){
  return s.elements[s.n-1];
}

void empty(Stack * s){
  s->n=0;
}

void print(Stack s){
  printf("Stack with %d elements:\n", s.n);
  for(int i=0;i<s.n;i++)
    printf("%d ", s.elements[i]);
  printf("\n");
}

