.text
.global copyarray

copyarray:
    ldr r2, [r0], #4
    str r2, [r1], #4
    sub r3, r3, #1
    cmp r3, #0
    bne copyarray
    mov pc, lr
