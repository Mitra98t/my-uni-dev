//https://drive.google.com/open?id=1CEp1CMabxTz6xXCORL3ahx1jxOw_HUnt

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
    ANONIMI l = NULL;
    int buff = -1;
    int n = 0;

    while (buff != 0)
    {
        if (scanf("%d", &buff) != 1 || buff < 0)
        {
            printf("Inserisci intero positivo o 0 per uscire\n");
            scanf("%*[^\n]\n");
        }
        else
        {
            if (buff > 0)
                add_end(&l, buff);
        }
    }

    // printf("%d\n", RecLength(l));

    printf("Stampa l'elenco in ordine inverso di immissione (NULL se vuota):\n");
    RecStampaInversa(l);
    printf("NULL \n");

    printf("Inserisci il numero richiesto:\n");
    scanf("%d", &n);

    CancellaMultipli(&l, n);

    printf("Stampa l'elenco in ordine di immissione (NULL se vuota):\n");
    RecStampa(l);

    printf("Dispari:%d\n", firstDispari(l));

    printf("Pari:%d\n", firstPari(l));

    return 0;
}