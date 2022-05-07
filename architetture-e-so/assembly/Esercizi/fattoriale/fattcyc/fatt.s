.text
.global fatt

fatt:
    mov r1, r0
loop:
    sub r1, r1, #1
    cmp r1, #0
    movle pc, lr
    mul r0, r1, r0
    b loop
