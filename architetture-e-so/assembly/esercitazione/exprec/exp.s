.text
.global exprec

exprec:
    cmp r1, #0
    moveq r0, #1
    moveq pc,lr
    push {lr}       @ salvo link register
    push {r0}
    sub r1, r1, #1  @ calcolo n-1
    bl exprec
    pop {r2}
    mul r0, r0, r2
    pop {pc}
    
