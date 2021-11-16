.text
.global convertslim
.type converti, %function

convertslim:
    cmp r0, #58
    sublt r0, r0, #48
    subge r0, r0, #87
    mov pc, lr
