.globl factorial

.data
n: .word 10

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    add t0, a0, x0
    addi, a0, x0, 1
loop:
    beq t0, x0, end
    mul a0, a0, t0
    addi t0, t0, -1
    j loop
end:
    jr ra #jalr x0, ra, 0



