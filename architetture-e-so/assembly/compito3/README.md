# Compito 3 Assembly

Si richiede di scrivere una procedura `void trasforma(char \*s, char\* from, char \* to, int N)` che trasforma una stringa di caratteri ASCII, terminata dal carattere di codice 0, secondo il seguente algoritmo:

- per ogni carattere della stringa s
  - se il carattere appare nel vettore `from[N]` alla posizione j, si sostituisce il carattere nella stringa originaria con il carattere che compare nel vettore `to[N]` alla stessa posizione j;
  - se il carattere non compare nel vettore `from[N]` non si effettua alcuna sostituzione.

Il vettore `from[N]` non è necessariamente ordinato. Se avessimo due vettori da 3 posizioni ciascuno:

```C
char from[] = {‘u’, ‘n’, ‘b’};  
char to[] = {‘a’, ‘b’, ‘c’};
```

la trasforma della stringa "buongiorno!" produrrebbe come risultato la stringa "caobgiorbo!"

Si richiede che `trasforma` venga implementata utilizzando una seconda funzione "ausiliaria" `char cambia(char c, char*from, char* to, int N)` che cerchi `c` in `from[]` e in caso lo trovi (per esempio alla posizione `j`) restituisca `to[j]`, diversamente restituisca `c`.

Per testare il codice, supponendo che le due funzioni siano definite nei file `trasforma.s` e `cambia.s` possiamo utilizzare il seguente file `test.c`:

```C
include <stdio.h>

# include <stdlib.h>
# include <string.h>

extern void trasforma(char *, char*, char *, int);

int main(int argc, char ** argv) {

    int N = 5;
    char from[] = {'a', 'e', 'i', 'o', 'u'};
    char to  [] = {'x', 'y', 'w', 'z', 'h'};

    char *s[] = {"", "u", "cmpxt", "aiuoe", "vediamo come va con questa frase"};
    char*ok[] = {"", "h", "cmpxt", "xwhzy", "vydwxmz czmy vx czn qhystx frxsy"};
    int nw = 5;

    int i;
    for(i=0; i<nw; i++) {
        char *tmp = (char*) malloc(strlen(s[i])+1);
        strcpy(tmp, s[i]);

        trasforma(tmp, from, to, N);

        if(strcmp(tmp, ok[i]) == 0) {
            printf("OK <%s> -> <%s>\n", s[i], tmp);
        } else {
            printf("Errore: %s dovrebbe essere %s\n", tmp, ok[i]);
        }
  }
  return(0);
}
```

Compilando I tre file con `gcc –o main test.c trasforma.s cambia.s` ed eseguendo il programma, si ottiene una stampa che dice se il codice calcola quanto richiesto su una serie di stringhe campione.
