.data
a1: .word 7,8,2,4,3,9,15
s: .string "%d "
.text
.global main

main:
    ldr r0, =a1
    mov r1, #7
    push {lr}
    bl bubbles
    mov r2, r0
    mov r3, r1
    push {r4}
    mov r4, #0
    ldr r0, =s
loop:
    ldr r1, [r2], #4
    bl printf
    ldr r0, =s
    add r4, r4, #1
    cmp r4, r3
    blt loop
    pop {r4}
    pop {pc}
