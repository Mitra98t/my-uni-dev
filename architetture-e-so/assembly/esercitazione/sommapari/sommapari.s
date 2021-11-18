.text
.global sommapari

sommapari:
    push {r4}
    mov r4, #0

loop:
    ldr r2, [r0], #4
    and r3, r2, #1
    cmp r3, #1
    addeq r4, r4, r2
    sub r1, r1, #1
    pop {r4}
    mov pc, lr
