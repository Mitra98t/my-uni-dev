.data
res:    .string "result %d\n"

.text
.global main

main:
    push {lr}
    mov r0, #3
    mov r1, #3
    bl exprec
    mov r1, r0
    ldr r0, =res
    bl printf
    pop {pc}
    
