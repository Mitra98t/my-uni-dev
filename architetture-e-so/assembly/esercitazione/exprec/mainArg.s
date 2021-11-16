.data
res:    .string "result %d\n"

.text
.global main

main:
    push {lr}
    ldr r0, [r1, #4]
    push {r0}
    ldr r0, [r1, #8]
    bl atoi
    mov r1, r0
    pop {r0}
    push {r1}
    bl atoi
    pop {r1}
    bl exprec
    mov r1, r0
    ldr r0, =res
    bl printf
    pop {pc}
