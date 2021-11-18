.text
.global somma

somma:
    mov r3, #0
    mov r1, r0
loop:
    ldrb r0, [r1], #1
    cmp r0, #0
    beq end
    push {lr}
    bl quanto
    pop {lr}
    add r3, r3, r0
    b loop

end:
    mov r0, r3
    mov pc, lr

quanto:
    sub r2, r0, #0x30
    cmp r2, #0
    cmpge r2, #9
    movgt r0, #0
    movle r0, r2
    mov pc, lr
