/*
Scrivere una funzione in C 

int copyFile(const char* source, const char* dest) 

che copia i contenuti del file "source" nel file "dest". La funzione utilizza un buffer di dimensione fissa (una costante) per processare i contenuti. La funzione restituisce 0 se la copia è stata fatta con successo, 1 in caso di errore. Non cambiare la funzione "main" e i due file che trovate su REPL, servono per testare la funzione
*/

#include <stdio.h>
#include <stdlib.h>

#define BUFF 1

int copyFile(const char *source, const char *dest);

int main(void)
{
    char f1[100], f2[100];
    char command[100];
    scanf("%s %s", f1, f2);
    int res = copyFile(f1, f2);
    if (!res)
    {
        sprintf(command, "diff %s %s", f1, f2);
        system(command);
        printf("\nEnd diff.");
    }
    else
    {
        printf("Copy failed.\n");
    }
}

int copyFile(const char *source, const char *dest)
{
    FILE *in = fopen(source, "rb");
    FILE *out = fopen(dest, "wb");
    char c[BUFF];
    int length = 0;
    if (in)
    {
        do
        {
            length = fread(c, sizeof(char), BUFF, in);
            if (length)
                fwrite(c, sizeof(char), length, out);
        } while (length);
    }
    else
    {
        return 1;
    }
    fclose(in);
    if (ferror(out))
    {
        return 1;
    }
        fclose(out);
    return 0;
}
