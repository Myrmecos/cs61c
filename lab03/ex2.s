.data
source:
    .word   3
    .word   1
    .word   4
    .word   1
    .word   5
    .word   9
    .word   0
dest:
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0

.text
#t0 = k; s0 = a; s1 = b; s2 = c; s3 = d;t1 = l; t2 = m
main:
    addi t0, x0, 0 #k = 0
    addi s0, x0, 0 #a = 0
    la s1, source #b = sourceArr
    la s2, dest #s2 = destArr
loop:
    slli s3, t0, 2 # d = k << 2 
    add t1, s1, s3 #l = b + d
    lw t2, 0(t1) # m = sourceArr[l]
    beq t2, x0, exit #if sourceArr[l] == 0: exit.
    add a0, x0, t2
    addi sp, sp, -8
    sw t0, 0(sp)
    sw t2, 4(sp)
    jal square
    lw t0, 0(sp)
    lw t2, 4(sp)
    addi sp, sp, 8
    add t2, x0, a0
    add t3, s2, s3
    sw t2, 0(t3)
    add s0, s0, t2
    addi t0, t0, 1
    jal x0, loop
square:
    add t0, a0, x0
    add t1, a0, x0
    addi t0, t0, 1
    addi t2, x0, -1
    mul t1, t1, t2
    mul a0, t0, t1
    jr ra
exit:
    add a0, x0, s0
    add a1, x0, x0
    ecall # Terminate ecall