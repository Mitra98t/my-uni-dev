.text
.global fatt

fatt:
    cmp r0, #1
    movle pc, lr
    push {lr}
    push {r0}
    sub r0, r0, #1
    bl fatt
    pop {r1}
    mul r0, r0, r1
    pop {pc}
