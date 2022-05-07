.data
res:    .string "il risultato è %d\n"

.text
.global main

main:
    push {lr}
    mov r0, #4
    bl fibonacci
    mov r1, r0
    ldr r0, =res
    bl printf
    pop {pc}
