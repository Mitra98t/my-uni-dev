.data
str:    .string "parola"
res:    .string "%s\n"
.text
.global main

main:
    ldr r0, =str
    push {lr}
    bl revstr
    mov r1, r0
    ldr r0, =res
    bl printf
    pop {pc}
