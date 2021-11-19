@ r0 => stringa
@ r1 => from
@ r2 => to
@ r3 => n

.text
.global trasforma

trasforma:
    push {r0, r4, r5}   @ push r0 per mantenere il puntatore alla testa
fort:
    ldrb r4, [r0]       @ carico primo carattere
    cmp r4, #0          @ confronto con end of string
    beq endt            @ se fine stringa chiudo
    push {lr}           
    push {r0, r4}       
    mov r0, r4          @ metto il carattere considerato in r0
    bl cambia           
    mov r4, r0          @ metto il carattere restituito da cambia in r4
    pop {r0, r5}        
    pop {lr}
    cmp r4, r5          @ confronto il nuovo con il vecchio carattere
    strneb r4, [r0]     @ se sono diversi sostituisco
    add r0, r0, #1      @ incremento il puntatore
    b fort
endt:
    pop {r0, r4, r5}    
    mov pc, lr          
