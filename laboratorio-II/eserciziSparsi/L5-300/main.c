//https://drive.google.com/open?id=1AxZJVPbvQsjj2ce0jS6no0tsqWi6_WTx
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void){

    List l = NULL;
    List l1 = NULL;

    int buff = 0;

    do
    {
        scanf("%d", &buff);
        if(buff >= 0){
            addHead(&l, buff);
        }
    } while (buff >= 0);

    insNegOnesRec(&l, &l1);

    print(l);

    return 0;
}