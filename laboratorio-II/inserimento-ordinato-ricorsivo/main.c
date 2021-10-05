//pila con liste concatenate
#include <stdlib.h>
#include <stdio.h>
#include "List.h"
//#include "Stack.h"

int main()
{

  List l = NULL;

  insertOrdRec(&l, 10);
  insertOrdRec(&l, 1);
  insertOrdRec(&l, 100);
  insertOrdRec(&l, 5);
  insertOrdRec(&l, 7);
  printList(l);

  freeListR(&l);
  printList(l);

  /*
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
  */

  return 0;
}

//inserimento ordinato in lisa