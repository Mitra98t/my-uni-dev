#include<stdio.h>
#include<string.h>
#include<stdlib.h>

extern char cifra(char, int);
extern int cambia(char *, int);

int main(int argc, char **argv)
{
    char *s = (char *) malloc(100);
    char *r = (char *) malloc(100);
    int shift = 0;
    scanf("%s", s);
    scanf("%d", &shift);
    // strcpy(s, "tocco2001");
    strcpy(r,s); 
    int c = cambia(s, shift);
    printf("OldStr: %s\nString: %s\nChanged: %d\n", r, s, c);
    return(0);
}
