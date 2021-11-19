@ r0 => stringa
@ r1 => from
@ r2 => to
@ r3 => n

.text
.global trasforma

trasforma:
    push {r0, r4, r5}
fort:
    ldrb r4, [r0]
    cmp r4, #0
    beq endt
    push {lr}
    push {r0, r4}
    mov r0, r4
    bl cambia
    mov r4, r0
    pop {r0, r5}
    pop {lr}
    cmp r4, r5
    strneb r4, [r0]
    add r0, r0, #1
    b fort
endt:
    pop {r0, r4, r5}
    mov pc, lr

@ r0 => carattere
@ r1 => from
@ r2 => to
@ r3 => n

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
