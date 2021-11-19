        .data
a1:     .word 3,1,8,7
a2:     .space 16
s:      .string "stampo %d\n"

        .text
        .global main

main:
        push {r4}
        ldr r0, =a1
        ldr r4, =a2
        mov r1, #4
        push {r4, lr} 
        bl bsort
        pop {r4, lr}
        mov r2, #4
        mov r3, r4
        ldr r0, =s

for:
        cmp r2, #0
        ble endmain
        ldr r1, [r3], #4
        sub r2, r2, #1
        push {r0-r3}
        bl printf
        pop {r0-r3}
        b for

endmain:
        pop {r4}
        mov pc, lr

bsort:                           

    push    {R4-R7,LR}          

succ:                           

    mov     R2,#0               
    mov     R6,#0               

loop:                           

    add     R3,R2,#1            
    cmp     R3,R1               
    bge     controllo           
    ldr     R7,[R0,R2,LSL #2]   
    ldr     R5,[R0,R3,LSL #2]   
    cmp     R7,R5               
    strgt   R5,[R4,R2,LSL #2]     
    strgt   R7,[R4,R3,LSL #2]     
    addgt   R6,R6,#1              
    mov     R2,R3               
    b       loop

controllo:                      

    cmp     R6,#0               
    subgt   R1,R1,#1              
    bgt     succ                

fine:                           

    pop     {R4-R7,PC}          
