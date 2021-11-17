.text
.global copyarray

copyarray:
    mov r3, #0
loop:
    ldr r2, [r0], #4
    str r2, [r1], #4
    add r3, r3, #1
    cmp r3, #4
    bne loop
    mov pc, lr
