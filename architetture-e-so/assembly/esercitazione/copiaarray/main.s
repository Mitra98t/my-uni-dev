.data
a1:     .word 1,2,3,4   @ dichiaro array statico
a2:     .space 16       @ alloco 16 byte
str:    .string "el: %d\n"

.text
.global main

main:
    ldr r0, =a1
    ldr r1, =a2
    push {lr}
    bl copyarray
    ldr r0, =str
    ldr r1, =a2
    mov r3, #0
loop:
    bl printf
    add r3, r3, #1
    cmp r3, #3
    bne loop
    pop {pc}    
