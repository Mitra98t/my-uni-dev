	.text
	.global SumEven

SumEven:
    PUSH {r4}
	MOV r2, #0 @Contiene la somma
LOOP:	
    CMP r1, #0
	BEQ FINE
	LDR r3, [r0], #4 @Contiene x[i]
	AND r4, r3, #1
	CMP r4, #1
	BEQ SUB
	ADD r2, r2, r3
SUB:	
    SUB r1, r1, #1
	B LOOP
FINE:	MOV r0, r2
	POP {r4}
	MOV PC, LR
	
