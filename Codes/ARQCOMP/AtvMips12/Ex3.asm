# MARCELO FERREIRA DE ALMEIDA
.data
	mes: .asciiz "Digite numero de valores: "  
	st: .asciiz "Digite valor: "               

.text
    li $v0, 4# Carrega a syscall 4 (imprimir string)
    la $a0, mes  # Carrega o endereço da mensagem para $a0
    syscall

    li $v0, 5  # Carrega a syscall 5 (ler inteiro)
    syscall
    move $t1, $v0  # Move o valor lido (número de valores) para $t1
    li $t2, 0   # Inicializa $t2 (contador) com 0

loop:
    li $v0, 4     # Carrega a syscall 4 (imprimir string)
    la $a0, st # Carrega o endereço da mensagem para $a0
    syscall

    li $v0, 5  # Carrega a syscall 5 (ler inteiro)
    syscall
    move $a1, $v0  # Move o valor lido para $a1 (valor atual)
    move $a0, $t0  # Move o valor anterior para $a0
    jal gcd   # Chama a função 'gcd'
    move $t0, $v0  # Move o resultado do GCD para $t0
    addi $t2, $t2, 1    # Incrementa o contador
    bne $t2, $t1, loop  # Se o contador não for igual ao número de valores, repete o loop

    move $a0, $t0    # Move o resultado final para $a0
    li $v0, 1   # Carrega a syscall 1 (imprimir inteiro)
    syscall

    li $v0, 10   # Carrega a syscall 10 (sair do programa)
    syscall

gcd:
    beq $a1, $0, return # Se o segundo argumento for zero, retorna
    divu $a0, $a1  # Divide o primeiro pelo segundo argumento
    move $a0, $a1  # Move o segundo argumento para $a0
    mfhi $a1  # Move o resto da divisão para $a1
    bnez $a1, gcd   # Se o resto não for zero, chama recursivamente 'gcd'
return:
    move $v0, $a0   # Move o resultado final para $v0
    jr $ra  # Retorna à chamada anterior
