.data
res:	.string "%d "
a1:	.word 1,2,3,1,2,3,1,2,3,1,2,3 
.text
.global main

main:
	push {lr}
	ldr r0, =a1
	push {r0}
	mov r1, #12
	mov r2, #2
	bl filter
	mov r3, r0
	mov r2, #0
	pop {r1}
	push {r4}
	mov r4, r1
	ldr r0, =res
loop:
	ldr r1, [r4], #4
	push {r0-r4}
	bl printf
	pop {r0-r4}
	add r2, r2, #1
	cmp r2, r3
	bne loop
	pop {r4}
	pop {pc}
