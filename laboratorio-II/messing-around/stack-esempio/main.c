//pila con liste concatenate
#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"
// #include "List.h"

int main(){

/*
  List l=NULL;

  insertOrd(&l,10);
  insertOrd(&l,1);
  insertOrd(&l,100);
  insertOrd(&l,5);
  insertOrd(&l,7);
  printList(l);

  freeListR(&l);
  printList(l);
*/
  Stack s = NULL;
  print(s);

  push(&s,5.4);
  print(s);

  push(&s,10.3);
  print(s);

  printf("Elemento in cima %f\n",top(s));
  print(s);
  
  printf("Elemento in cima %f\n",pop(&s));
  print(s);

  printf("Elemento in cima %f\n",pop(&s));
  print(s);

  printf("Elemento in cima %f\n",pop(&s));
  print(s);
  
  freeS(&s);
  print(s);
  return 0;
}



//inserimento ordinato in lisa