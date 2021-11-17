.data
s:  .string "ciao"

.text
.global main

main:
    push {lr}
    bl pal
    mov r1, r0 
    ldr r0, =s
    bl printf
    pop {pc}
