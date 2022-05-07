    .data
s:  .string "f0a1"
f:  .string "Il valore della stringa è %d\n"
    .text
    .global main

main:
     push {lr}
     ldr r0, =s
     bl convstring
     mov r1, r0
     ldr r0, =f
     bl printf
     pop {pc}
