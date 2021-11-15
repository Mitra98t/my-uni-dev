.text
.global cifra

cifra:
    cmp r0, #0x7a
    cmpls r0, #0x61
    blo end
    add r0, r0,r1
    cmp r0,#0x7a
    bls end
    sub r0, r0, #0x7a
    add r0, r0, #0x61
    sub r0, r0, #1

end:
    mov pc,lr
