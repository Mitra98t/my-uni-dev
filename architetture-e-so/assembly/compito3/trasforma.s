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
