/*
    Scrivere un FSM che controlli stringhe del tipo:
    ^[A-Z]{3}1+[A-Z]{2}$
*/
#include <stdio.h>
#include <string.h>

#define DIM 100
#define STATE_COUNT 8

typedef enum
{
    S0,
    S1,
    S2,
    S3,
    S4,
    S5,
    S6,
    ERR
} State;

// Sono accorpati gli stati s0125 per rispettare la regola dry
State s0125(char c, State currS)
{
    if (c >= 'A' & c <= 'Z')
    {
        return currS + 1;
    }
    else
    {
        return ERR;
    }
}
State s3(char c, State currS)
{
    if (c == '1')
    {
        return S4;
    }
    else
    {
        return ERR;
    }
}
State s4(char c, State currS)
{
    if (c == '1')
    {
        return S4;
    }
    else if (c >= 'A' & c <= 'Z')
    {
        return S5;
    }
    else
    {
        return ERR;
    }
}
State s6err(char c, State currS)
{
    return ERR;
}

int main(void)
{

    State s = S0;
    char str[DIM];

    State (*automa[STATE_COUNT])(char, State) = {s0125, s0125, s0125, s3, s4, s0125, s6err, s6err};

    scanf("%[^\n]", str);

    for (int i = 0; i < strlen(str); i++)
    {
        // Passo la stringa alla funzione salvata in un array di puntatori a funzione.
        // salvo lo stato di return in s e ciclo
        s = (*automa[s])(str[i], s);
    }

    if (s == S6)
    {
        printf("Parola accettata\n");
    }
    else
    {
        printf("Parola non accettata\n");
    }

    return 0;
}