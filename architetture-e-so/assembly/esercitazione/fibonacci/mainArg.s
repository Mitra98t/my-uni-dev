.text
.global main

.data
res:    .string "fibo(%d) = %d\n"

main:
    push {lr}
    ldr r0, [r1, #4]
    bl atoi
    push {r0}
    bl fibonacci
    mov r2, r0
    pop {r1}
    ldr r0, =res
    bl printf
    pop {pc}
