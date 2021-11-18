.data
a1: .word 1,2,3,4,5,6,7,8,9,10

.text
.global main

main:
    ldr r0, =a1
    mov r1, #10
    push {lr}
    bl sommapari
    pop {pc}
