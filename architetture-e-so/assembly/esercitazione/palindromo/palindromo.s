@ r0 => string index

.text
.global pal

pal:
    push {lr}
    mov r1, #0
    push {r0}
    b getlen
    pop {r2}
    pop {pc}

getlen:
    ldrb r2, [r0], #1
    cmp r2, #0
    moveq r0, r1
    moveq pc, lr
    add r1, r1, #1
    b getlen
