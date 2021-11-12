     .text
     .global fun

fun: ADD r0,r0,r1
     ASR r0,r0,#1
     MOV pc,lr