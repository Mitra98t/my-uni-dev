@r0 => array  r1 => dimensione array  r2 => elemento da filtrare

.text
.global filter

filter:
	push {r4, r5, r6}
	mov r3, #0
	mov r5, #0
	mov r6, r1
for: 
	ldr r4, [r0]
	cmp r4, r2
	addne r0, r0, #4
	addne r3, r3, #1
	push {lr}
	bleq rmv
	pop {lr}
	cmp r3, r6
	ble for
	mov r0, r6
	pop {r4-r6}
	mov pc, lr
	
rmv: 
	add r5, r5, #1
	sub r6, r6, #1
	push {r0, r3}
forRmv: 
	ldr r4, [r0, #4]
	str r4, [r0], #4
	add r3, r3, #1
	cmp r3, r6
	ble forRmv
	pop {r0, r3}
	mov pc, lr
