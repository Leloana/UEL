# MARCELO FERREIRA DE ALMEIDA
.data
	mes1: .asciiz "Digite um numero no sistema binario:\n"  
	mes2: .asciiz "Numero binario:\n"                      
	mes3: .asciiz "Nao eh um numero binario!"                
	bsn: .asciiz "\n"                                       

	num: .word 0  # Variável para armazenar o número binário digitado
	num1: .word 0 # Variável para armazenar uma cópia do número binário
	count: .word 0  # Contador para o loop de conversão
	val: .word 0  # Variável temporária para armazenar o valor de um dígito binário
	decim: .word 0  # Variável para armazenar o valor decimal do número binário
	base: .word 0  # Base para o cálculo do valor decimal
	lastdigit: .word 0 # Último dígito do número binário

.text
main:
    li $v0, 4  # Carrega a syscall 4 (imprimir string)
    la $a0, mes1  # Carrega o endereço da mensagem para $a0
    syscall

    la $s0, num  # Carrega o endereço de num para $s0
    la $s1, num1  # Carrega o endereço de num1 para $s1
    la $s2, count  # Carrega o endereço de count para $s2
    la $s3, val     # Carrega o endereço de val para $s3
    la $s4, decim   # Carrega o endereço de decim para $s4
    la $s5, base   # Carrega o endereço de base para $s5
    la $s6, lastdigit   # Carrega o endereço de lastdigit para $s6

    li $v0, 5   # Carrega a syscall 5 (ler inteiro)
    syscall
    sw $v0, 0($s0)   # Armazena o número lido em num
    lw $t0, 0($s0)   # Carrega o número binário para $t0
    sw $t0, 0($s1)   # Armazena uma cópia do número binário em num1
    lw $t0, 0($s1)  # Carrega o número binário para $t0
    lw $t2, 0($s3)  # Carrega 0 em $t2 (valor temporário)
    lw $t4, 0($s2) # Carrega 0 em $t4 (contador)

loop:  
    beq $t0, $zero, exit  # Se $t0 for zero, encerra o loop
    addi $t1, $zero, 10   # $t1 = 10 (base para divisão)
    div $t0, $t1   # Divide $t0 por 10
    mfhi $t2   # Move o resto da divisão para $t2
    addi $t3, $zero, 1    # $t3 = 1 (valor temporário)
    beq $t2, $t3, s   # Se o resto for 1, vá para 's'
    beq $t2, $zero, s     # Se o resto for 0, vá para 's'
    addi $t4, $t4, 1   # Incrementa o contador
    addi $t5, $zero, 10   # $t5 = 10 (base para divisão)
    div $t0, $t0, $t5     # Divide $t0 por 10
    j loop                # Volta ao início do loop

s:
    addi $t5, $zero, 10   # $t5 = 10 (base para divisão)
    div $t0, $t0, $t5   # Divide $t0 por 10
    j loop  # Volta ao INICIO do loop

exit: 
    li $v0, 4  # Carrega a syscall 4 (imprimir string)
    la $a0, bsn  # Carrega o endereço de bsn para imprimir quebra de linha
    syscall

    bne $t4, $zero, no    # Se o contador não for zero, vá para 'no'
    li $v0, 4    # Carrega a syscall 4 (imprimir string)
    la $a0, mes2 # Carrega o endereço de mes2 para imprimir
    syscall
    lw $t0, 0($s0)  # Carrega o número binário para $t0
    lw $t1, 0($s4)   # Carrega o contador para $t1
    lw $t2, 0($s5)   # Carrega a base para $t2
    lw $t3, 0($s6) # Carrega o último dígito para $t3
    addi $t2, $zero, 1    # $t2 = 1 (base para cálculo do dígito decimal)

loop1:  
    beq $t0, $zero, out   # Se $t0 for zero, saia do loop
    addi $t5, $zero, 10   # $t5 = 10 (base para divisão)
    div $t0, $t5   # Divide $t0 por 10
    mfhi $t3    # Move o resto para $t3
    div $t0, $t0, $t5     # Divide $t0 por 10
    mul $t6, $t3, $t2     # Multiplica o último dígito pelo valor da base
    add $t4, $t4, $t6     # Adiciona o resultado ao número decimal
    addi $t7, $zero, 2    # $t7 = 2 (base binária)
    mul $t2, $t2, $t7  # Multiplica a base por 2
    j loop1  # Volta ao início do loop

out:  
    li $v0, 1   # Carrega a syscall 1 (imprimir inteiro)
    move $a0, $t4 # Move o número decimal para $a0
    syscall 
    j exit_program

no: 
    li $v0, 4 # Carrega a syscall 4 (imprimir string)
    la $a0, mes3    # Carrega o endereço de mes3 para imprimir a mensagem de erro
    syscall

exit_program:
    li $v0, 10 # Carrega a syscall 10 (sair do programa)
    syscall
