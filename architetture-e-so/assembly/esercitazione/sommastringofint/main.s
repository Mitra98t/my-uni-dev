.data
str:    .string "12c3acc4a5"
res:    .string "%d\n"

.text
.global main

main:
    ldr r0, =str
    push {lr}
    bl somma
    mov r1, r0 
    ldr r0, =res
    bl printf
    pop {pc}
