.data
s:      .string "baab"
res:    .string "palindromo: %d\n"

.text
.global main

main:
    push {lr}
    ldr r0, =s
    bl pal
    mov r1, r0 
    ldr r0, =res
    bl printf
    pop {pc}
