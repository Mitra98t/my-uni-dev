.data
a1: .word 7,8,2,4,3,9,15

.text
.global main

main:
    ldr r0, =a1
    mov r1, #7
    push {lr}
    bl bubbles
    pop {pc}
