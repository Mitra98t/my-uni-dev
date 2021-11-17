.data
a1: .word 1,2,3,4
a2: .word 0,0,0,0

.text
.global main

main:
    ldr r0, [a1]
    ldr r1, [a2]
    push {lr}
    bl copyarray
    pop {pc}    
