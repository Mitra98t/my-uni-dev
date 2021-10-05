/*Implementare una pila con operazioni push, pop, top, empty 
*/

/* Usare la pila per valutare espressioni in notazione polaca inversa: 
(45+3*2)/18
45 3 2 * +    18 /  - per questa non funzioan
45 3 2 * * 18 /

! QUESTO PROGRAMMA FUNZIONA SOLO PER ESPRESSIONI CHE NON UTILIZZANO GLI OPERATORI - E + . LA PROSSIMA SETTIMANA SCRIVIAMO UN ALTRO PROGRAMMA PIU' GENERALE.
*/

#include <stdio.h>
#include "stack.h"
#include <stdlib.h>

int main(){

  Stack p;
  p.n=0;
  //lettura espressione

  int n, a, b;
  char o=' ',o1;

  while(o!='\n'){
    print(p);
    if(scanf("%d",&n)==1){ //se questo scanf trova un + o un -, lo consuma provando a leggere un intero. quindi la strategia funziona solo per espressioni con operatori * e /
      //printf("1 operando %d \n",n);
      push(n,&p);
    } else {
      scanf("%c",&o);
      //printf("2 _%c_\n",o);
      
      if(o!='\n'){
        switch(o){
          case '+':
            b=pop(&p);
            a=pop(&p);
            push(a+b, &p);
            break;
          case '-':
            b=pop(&p);
            a=pop(&p);
            push(a-b, &p);
            break;
          case '*':
            b=pop(&p);
            a=pop(&p);
            push(a*b, &p);
            break;
          case '/':
            b=pop(&p);
            a=pop(&p);
            push(a/b, &p);
            break;
        }
      }
      scanf("%c",&o);
      //printf("3 _%c_\n",o);
    }
  }

  print(p);
  
}