@ r0 => carattere
@ r1 => from
@ r2 => to
@ r3 => n

.text
.global cambia

cambia:
    push {r4, r5}
    mov r5, #0
forsearch:
    ldrb r4, [r1, r5]
    cmp r4, r0
    beq sostituto
    add r5, r5, #1
    cmp r5, r3
    bge endcambia
    b forsearch

sostituto:
    cmp r5, r3
    bge endcambia
    ldrb r0, [r2, r5]

endcambia:
    pop {r4, r5}
    mov pc, lr
