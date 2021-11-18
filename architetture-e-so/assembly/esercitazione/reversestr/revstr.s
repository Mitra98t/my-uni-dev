.text
.global revstr

revstr:
    push {lr}
    bl getfirstlastpointer
    push {r0}
forrev:
    ldrb r2, [r0]
    ldrb r3, [r1]
    strb r2, [r1]
    strb r3, [r0]
    sub r2, r1, r0
    cmp r2, #1
    addgt r0, r0, #1
    subgt r1, r1, #1
    bgt forrev
    
    pop {r0}
    pop {pc}



getfirstlastpointer:
    mov r1, r0
forgflp:
    ldrb r2, [r1], #1
    cmp r2, #0
    subeq r1, r1, #2
    moveq pc, lr
    b forgflp
    
