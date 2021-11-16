@ r0 => cifra in hex

.text
.global convert

convert:
    cmp r0, #48     @ 0
    cmpge r0, #57   @ 9
    ble cifra
    cmp r0, #97     @ a
    cmpge r0, #102  @ f
    ble lettera
    b end

cifra:
    sub r0, r0, #48
    b end

lettera:
    sub r0, r0, #87
    b end

end:
    mov pc,lr    
