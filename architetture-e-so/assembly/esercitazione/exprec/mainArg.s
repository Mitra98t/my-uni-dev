.data
res:    .string "result %d\n"

.text
.global main

main:
    push {lr}
    ldr r0, [r1, #4]!
    ldr r1, [r1, #4]
    bl atoi
    bl exprec
    mov r1, r0
    ldr r0, =res
    bl printf
    pop {pc}
