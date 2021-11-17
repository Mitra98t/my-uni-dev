@ r0 => string index

.text
.global pal

pal:
    push {lr}
    push {r0}
    b getlastpointer
    mov r1, r0
    pop {r0}
    cmp r0, r1
    movle r0, #1
    movle pc, lr
    b confronta
    pop {pc}

getlastpointer:
    ldrb r2, [r0], #1
    cmp r2, #0
    subeq r0, r0, #2
    moveq pc, lr
    b getlastpointer

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
    

end:
    mov pc, lr
