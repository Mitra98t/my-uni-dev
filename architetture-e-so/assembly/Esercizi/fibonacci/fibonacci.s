.text
.global fibonacci

fibonacci:
    cmp r0, #1      @ Casi base
    movle pc, lr    @ restituisco r0
    push {lr}       @ salvo indirizzo di ritorno
    sub r0, r0, #1  @ calcolo n-1
    push {r0}       @ salvo n-1
    bl fibonacci    @ calcolo fibonacci(n-1)
    pop {r1}        @ riprendo n-1
    push {r0}       @ salvo fibonacci(n-1)
    sub r0, r1, #1  @ clacolo n-2
    bl fibonacci    @ clacolo fibonacci(n-2)
    pop {r1}        @ riprendo fibonacci(n-1)
    add r0, r0, r1  @ calcolo fibonacci(n-1)+fibonacci(n-2)
    pop {pc}        @ ritorno al chiamante
