# MARCELO FERREIRA DE ALMEIDA
.data
	matrix:         .space 100        
	mes_matrix:  .asciiz "Digite valores da matriz 5x5:\n"  
	mes_x: .asciiz "Digite valor de x: "  
	mes_y: .asciiz "Digite valor de y: " 
	newline: .asciiz "\n" 
	mes_matrix_new:	.asciiz "Matriz modificada:\n"  

.text
main:
    li $v0, 4 # $v0 = 4 (syscall para imprimir string)
    la $a0, mes_matrix # $a0 = endereço de mes_matrix (imprime "Digite valores para a matriz 5x5:")
    syscall

    la $t0, matrix # $t0 = endereço de matrix (início da matriz)
    li $t1, 0 # $t1 = 0 (contador para entrada da matriz)
    li $t2, 25 # $t2 = 25 (número total de elementos em uma matriz 5x5)

read_matrix:
    li $v0, 5 # $v0 = 5 (syscall para ler inteiro)
    syscall
    sw $v0, 0($t0) # Armazena o inteiro lido no endereço apontado por $t0
    addi $t0, $t0, 4 # Incrementa $t0 por 4 bytes (avança para o próximo inteiro)
    addi $t1, $t1, 1 # Incrementa $t1 por 1 (incrementa o contador)
    blt $t1, $t2, read_matrix  # Repete a leitura se $t1 for menor que $t2

    la $t0, matrix # Reinicia $t0 para o início da matriz
    li $t1, 0 # $t1 = 0

print_matrix:
    li $t2, 5 # $t2 = 5 (número de linhas da matriz)

print_matrix_line:
    lw $a0, 0($t0) # $a0 = valor na posição atual da matriz
    li $v0, 1 # $v0 = 1 (syscall para imprimir inteiro)
    syscall
    addi $t0, $t0, 4 # Incrementa $t0 por 4 bytes (avança para o próximo inteiro)
    addi $t2, $t2, -1 # Decrementa $t2 por 1 (decrementa o contador de linhas)
    bgtz $t2, print_matrix_line  # Repete a impressão da linha se $t2 for maior que 0

    li $v0, 4 # $v0 = 4 (syscall para imprimir string)
    la $a0, newline # $a0 = endereço de newline (imprime uma nova linha)
    syscall
    addi $t1, $t1, 1  # Incrementa $t1 por 1 (incrementa o contador de linhas impressas)
    li $t2, 5   # Reinicia $t2 para 5 (número de linhas da matriz)
    blt $t1, 5, print_matrix  # Repete a impressão da matriz se $t1 for menor que 5

    li $v0, 4     # $v0 = 4 (syscall para imprimir string)
    la $a0, mes_x     # $a0 = endereço de mes_x (imprime "Digite o valor de x:")
    syscall
    li $v0, 5    # $v0 = 5 (syscall para ler inteiro)
    syscall
    move $t8, $v0   # $t8 = $v0 (armazena o valor de x)

    li $v0, 4   # $v0 = 4 (syscall para imprimir string)
    la $a0, mes_y   # $a0 = endereço de mes_y (imprime "Digite o valor de y:")
    syscall
    li $v0, 5  # $v0 = 5 (syscall para ler inteiro)
    syscall
    move $t9, $v0 # $t9 = $v0 (armazena o valor de y)

    la $t0, matrix  # $t0 = endereço de matrix (início da matriz)
    mul $t2, $t8, 20   # $t2 = $t8 * 20 (deslocamento para a linha que contém o valor de x)
    add $t0, $t0, $t2  # Adiciona $t2 a $t0 (move para a linha que contém o valor de x)
    la $t1, matrix       # $t1 = endereço de matrix (início da matriz)
    mul $t3, $t9, 20    # $t3 = $t9 * 20 (deslocamento para a linha que contém o valor de y)
    add $t1, $t1, $t3   # Adiciona $t3 a $t1 (move para a linha que contém o valor de y)
    li $t4, 5  # $t4 = 5 (número de elementos por linha da matriz)

swap_rows:
    lw $t5, 0($t0)  # $t5 = valor na posição atual da linha de x
    lw $t6, 0($t1)  # $t6 = valor na posição atual da linha de y
    sw $t6, 0($t0) # Armazena $t6 na posição atual da linha de x
    sw $t5, 0($t1) # Armazena $t5 na posição atual da linha de y
    addi $t0, $t0, 4   # Incrementa $t0 por 4 bytes (avança para o próximo elemento na linha de x)
    addi $t1, $t1, 4    # Incrementa $t1 por 4 bytes (avança para o próximo elemento na linha de y)
    addi $t4, $t4, -1   # Decrementa $t4 por 1 (decrementa o contador de elementos)
    bnez $t4, swap_rows   # Repete a troca de linhas se $t4 for diferente de zero
    li $t4, 0  # $t4 = 0 (reinicia $t4)

swap_columns:
    la $t0, matrix  # $t0 = endereço de matrix (início da matriz)
    la $t1, matrix     # $t1 = endereço de matrix (início da matriz)
    mul $t2, $t4, 20     # $t2 = $t4 * 20 (deslocamento para a coluna que contém o valor de x)
    add $t0, $t0, $t2     # Adiciona $t2 a $t0 (move para a coluna que contém o valor de x)
    add $t1, $t1, $t2   # Adiciona $t2 a $t1 (move para a coluna que contém o valor de x)
    addi $t0, $t0, 4  # Incrementa $t0 por 4 bytes (avança para o próximo elemento na coluna de x)
    addi $t1, $t1, 4  # Incrementa $t1 por 4 bytes (avança para o próximo elemento na coluna de y)
    mul $t3, $t8, 4  # $t3 = $t8 * 4 (deslocamento para a posição do elemento de x)
    add $t0, $t0, $t3 # Adiciona $t3 a $t0 (move para a posição do elemento de x)
    mul $t3, $t9, 4  # $t3 = $t9 * 4 (deslocamento para a posição do elemento de y)
    add $t1, $t1, $t3   # Adiciona $t3 a $t1 (move para a posição do elemento de y)
    lw $t5, 0($t0)   # $t5 = valor na posição atual da coluna de x
    lw $t6, 0($t1)  # $t6 = valor na posição atual da coluna de y
    sw $t6, 0($t0) # Armazena $t6 na posição atual da coluna de x
    sw $t5, 0($t1)  # Armazena $t5 na posição atual da coluna de y
    addi $t4, $t4, 1    # Incrementa $t4 por 1 (incrementa o contador de colunas)
    blt $t4, 5, swap_columns  # Repete a troca de colunas se $t4 for menor que 5

    la $t0, matrix    # $t0 = endereço de matrix (início da matriz)
    la $t1, matrix       # $t1 = endereço de matrix (início da matriz)
    addi $t1, $t1, 16       # Adiciona 16 bytes a $t1 (move para a posição do segundo elemento na diagonal)
    li $t2, 0               # $t2 = 0 (reinicia $t2)

swap_diagonals:
    lw $t4, 0($t0)  # $t4 = valor na posição atual da diagonal principal
    lw $t5, 0($t1)  # $t5 = valor na posição atual da diagonal secundária
    sw $t5, 0($t0)  # Armazena $t5 na posição atual da diagonal principal
    sw $t4, 0($t1)# Armazena $t4 na posição atual da diagonal secundária
    addi $t0, $t0, 24   # Incrementa $t0 por 24 bytes (avança para o próximo elemento na diagonal principal)
    subi $t1, $t1, 16   # Subtrai 16 bytes de $t1 (avança para o próximo elemento na diagonal secundária)
    addi $t2, $t2, 1      # Incrementa $t2 por 1 (incrementa o contador de elementos na diagonal)
    blt $t2, 5, swap_diagonals  # Repete a troca de diagonais se $t2 for menor que 5

    li $v0, 4   # $v0 = 4 (syscall para imprimir string)
    la $a0, mes_matrix_new  # $a0 = endereço de mes_matrix_new (imprime "Matriz modificada:")
    syscall

    la $t0, matrix  # $t0 = endereço de matrix (início da matriz)
    li $t1, 0  # $t1 = 0 (reinicia $t1)

print_matrix_new:
    li $t2, 5               # $t2 = 5 (número de linhas da matriz)

print_matrix_line_new:
    lw $a0, 0($t0)  # $a0 = valor na posição atual da matriz
    li $v0, 1  # $v0 = 1 (syscall para imprimir inteiro)
    syscall
    addi $t0, $t0, 4  # Incrementa $t0 por 4 bytes (avança para o próximo inteiro)
    addi $t2, $t2, -1       # Decrementa $t2 por 1 (decrementa o contador de linhas)
    bgtz $t2, print_matrix_line_new  # Repete a impressão da linha se $t2 for maior que 0

    li $v0, 4  # $v0 = 4 (syscall para imprimir string)
    la $a0, newline # $a0 = endereço de newline (imprime uma nova linha)
    syscall
    addi $t1, $t1, 1 # Incrementa $t1 por 1 (incrementa o contador de linhas impressas)
    li $t2, 5  # Reinicia $t2 para 5 (número de linhas da matriz)
    blt $t1, 5, print_matrix_new  # Repete a impressão da matriz se $t1 for menor que 5

    li $v0, 10  # $v0 = 10 (syscall para encerrar o programa)
    syscall
