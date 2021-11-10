@ Sommare in un accumulatore elementi dell'array di valore pari

@ CMP src1, src2 || src1 - src2 => attiva dei flag - NON salva il risultato

     .text
    .global SumEven

SumEven:
    PUSH {r4}
    MOV r2, #0 @ int sum = 0; sum in registro r2
LOOP:
    CMP r1, #0 @ Confronta r1 (dimensione) con 0
    BEQ FINE @ Se r1 (dim) == 0 va a FINE
    LDR r3, [r0], #4 @ r3 prende il valore di r0 successivamente r0 viene incrementato di 4
    AND r4, r3, #1 @ metto in r4 l'AND tra r3 (arr[i]) e 1 => vedo se pari o dispari => r4 = 1 se dispari | 0 se pari
    CMP r4, #1 @ Resa vera se r4 dispari
    BEQ SKIP @ Va a SKIP se r4 dispari
    ADD r2, r2, r3 @ Se r4 pari => ADD || metto in r2 (accumulatore) la somma di r2 prima + r3 (arr[i])
SKIP:    
    SUB r1, r1, #1 @ diminuisco dimensione
    B LOOP 
FINE:
    MOV r0, r2 @ risultato di uscita conveznione in r0
    POP {r4} @ rimetto a posto registro r4 da preservare
    MOV PC, LR @ Restituisco controllo al chiamante (muovo link register -> program counter)

