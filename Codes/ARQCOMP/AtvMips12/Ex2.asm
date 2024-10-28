# MARCELO FERREIRA DE ALMEIDA
.data
	mes: .asciiz "Digite valor: "  

.text
    li $v0, 4# Carrega a syscall 4 (imprimir string)
    la $a0, mes # Carrega o endereço da mensagem para $a0
    syscall

    li $v0, 5# Carrega a syscall 5 (ler inteiro)
    syscall
    move $t0, $v0# Move o valor lido para $t0

    li $v0, 11  # Carrega a syscall 11 (imprimir caractere)
    li $a0, 10   # Carrega o código ASCII para 'nova linha'
    syscall

    li $v0, 4    # Carrega a syscall 4 (imprimir string)
    la $a0, mes   # Carrega o endereço de 'st' para imprimir
    syscall

    li $v0, 5     # Carrega a syscall 5 (ler inteiro)
    syscall
    move $a1, $v0   # Move o valor lido para $a1
    move $a0, $t0   # Move o primeiro valor lido para $a0
    jal gcd      # Chama a função 'gcd'
    move $a0, $v0# Move o resultado do GCD para $a0

    li $v0, 1  # Carrega a syscall 1 (imprimir inteiro)
    syscall

    li $v0, 10  # Carrega a syscall 10 (sair do programa)
    syscall

gcd:
    beq $a1, $0, return # Se $a1 (segundo argumento) for zero, retorna
    divu $a0, $a1    # Divide $a0 (primeiro argumento) por $a1
    move $a0, $a1   # Move $a1 para $a0
    mfhi $a1  # Move o resto da divisão para $a1
    bnez $a1, gcd   # Se $a1 não for zero, chama recursivamente 'gcd'
    j return  # Retorna

return:
    move $v0, $a0    # Move o resultado final para $v0
    jr $ra  # Retorna à chamada anterior
