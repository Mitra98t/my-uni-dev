.data
a1:     .word 1,2,3,4   @ dichiaro array statico
a2:     .space 16       @ alloco 16 byte

.text
.global main

main:
    ldr r0, =a1
    ldr r1, =a2
    mov r3, #4
    push {lr}
    bl copyarray
    pop {pc}  
