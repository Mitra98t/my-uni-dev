@ r0 => indirizzo della stringa

.text
.global convstring

convstring:
    mov r2, r0  @ indirizzo stringa
    mov r1, #0  @ r1 => sum
    push {lr}

loop:
    ldrb r0, [r2], #1   @ dopo aver caricato aggiungi 1
    cmp r0, #0
    beq end
    bl convertslim
    lsl r1, r1, #4      @ sum *= 16
    add r1, r1, r0
    b loop
    
end:
    mov r0, r1
    pop {lr}
    mov pc,lr
    
