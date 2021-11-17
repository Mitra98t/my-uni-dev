@ r0 => string index

.text
.global pal

pal:
    push {r0}

getlastpointer:
    ldrb r2, [r0], #1
    cmp r2, #0
    bne getlastpointer
    sub r0, r0, #2

    mov r1, r0
    pop {r0}
    cmp r1, r0
    movle r0, #1
    movle pc, lr

confronta:
    ldrb r2, [r0]
    ldrb r3, [r1]
    cmp r2, r3
    movne r0, #0
    movne pc, lr
    sub r2, r1, r0
    cmp r2, #1
    movle r0, #1
    movle pc, lr
    add r0, r0, #1
    sub r1, r1, #1
    b confronta
