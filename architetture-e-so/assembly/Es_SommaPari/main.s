	.data
      x:.word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    str:.string "La sommma finale e: %d\n"
	.text
	.global main

main:	LDR r0, =x
	MOV r1, #10 @Contiene la dimensione dell array
	PUSH {LR}
	BL SumEven
	MOV r1, r0
	LDR r0, =str
	BL printf
	MOV r0, #0
 	POP {LR}
	MOV PC, LR 
