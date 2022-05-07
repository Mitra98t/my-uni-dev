.text
.global sommeprefisse

sommeprefisse:
    push {r4}
    mov r4, #0
loop:
    ldr r2, [r0], #4
    add r4, r4, r2
    str r4, [r1], #4
    sub r3, r3, #1
    cmp r3, #0
    bne loop
    mov r0, r4
    pop {r4}
    mov pc, lr
