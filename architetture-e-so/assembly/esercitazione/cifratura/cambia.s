.text
.global cambia


noteq: 

cambia:	
	push {r4,lr}
	mov r2,#0 @ r2 = sum

loop:
	ldrb r3,[r0] @ iesimo carattere
    cmp r3,#0 @ controllo carattere '\0'
	beq end
	push {r0}
    mov r0,r3
	bl cifra 
	mov r4,r0 @ r4= cc
	pop {r0}
	cmp r4,r3
    mov r3, r4
	strneb r3, [r0]
	add r0,r0,#1 @incremento indirizzo carattere
	addne r2,r2,#1
    b loop

end:	
    pop {r4,lr}
	mov r0,r2
	mov pc,lr
