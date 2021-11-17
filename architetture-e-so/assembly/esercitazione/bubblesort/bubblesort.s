@ r0 => index array
@ r1 => length array

.text
.global bubbles

bubbles:
    push {r4, r5, r6}
    mov r2, #0
    mov r3, #0
    sub r1, r1, #1
for1:
    push {r0}
    mov r3, #0
for2:
    ldr r4, [r0], #4
    ldr r5, [r0]
    cmp r4, r5
    movgt r6, r4
    movgt r4, r5
    movgt r5, r6
    add r3, r3, #1
    cmp r3, r1
    bne for2
    
    pop {r0}
    add r2, r2, #1
    cmp r2, r1
    bne for1
    pop {r4, r5, r6}
    mov pc, lr
