.text
.global main

main:
    mov r0, #4
    push {lr}
    bl fatt
    pop {pc}
