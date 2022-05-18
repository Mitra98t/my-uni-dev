@ r0 => carattere
@ r1 => from
@ r2 => to
@ r3 => n

.text
.global cambia

cambia:
    push {r4, r5}
    mov r5, #0          @ intendo usare r5 come contatore
forsearch:
    ldrb r4, [r1, r5]   @ carico in r4 il carattere di dell'array r1 con offset r5
    cmp r4, r0          @ confronto con il carattere in input
    beq sostituto       @ se corrisponde vado alla sostituzione
    add r5, r5, #1
    cmp r5, r3          @ controllo fine dell'array
    bge endcambia       @ se array finito vado a endcambia
    b forsearch         

sostituto:
    cmp r5, r3          @ controllo se il contatore punta oltre l'array
    bge endcambia       @ se si vado a endcambia
    ldrb r0, [r2, r5]   @ carico in r0 il nuovo carattere

endcambia:
    pop {r4, r5}
    mov pc, lr
