.data
a1: .word 1,2,3,4
a2: .space 16

.text
.global main

main:
    ldr r0, =a1
    ldr r1, =a2
    mov r3, #4
    push {lr}
    bl sommeprefisse
    pop{pc}
