//https://drive.google.com/open?id=16D-Q4aQQrm72HkRqH3_VmsDkiGxT7v69

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
    List l = NULL;
    int buff = 0;
    int n = 0;
    do
    {
        scanf("%d", &buff);
        if (buff >= 0)
        {
            addTail(&l, buff);
        }
    } while (buff >= 0);

    scanf("%d", &n);
    inserisciQuarto(&l, n);
    print(l);
    return 0;
}