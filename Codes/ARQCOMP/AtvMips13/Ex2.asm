# MARCELO FERREIRA DE ALMEIDA

.data
	matriz_A:   .word 1, 2        # Linha 1 da matriz A
            .word 3, 4        # Linha 2 da matriz A
            .word 5, 6        # Linha 3 da matriz A
	matriz_B:   .word 7, 8, 9     # Coluna 1 da matriz B
            .word 10, 11, 12  # Coluna 2 da matriz B
	resultado:  .space 24         # Espaço para armazenar a matriz resultado (3 linhas x 2 colunas)

.text
main:
    # Inicializar os ponteiros das matrizes
    la $t0, matriz_A   # $t0 = endereço da matriz A
    la $t1, matriz_B   # $t1 = endereço da matriz B
    la $t2, resultado  # $t2 = endereço da matriz resultado

    # Calcular o produto de A por B
    li $t3, 0  # $t3 = índice da linha da matriz A
calculate_product_loop:
    beq $t3, 3, print_result   # Se todas as linhas de A foram processadas, imprimir o resultado
    li $t4, 0  # $t4 = índice da coluna da matriz B

calculate_column_loop:
    beq $t4, 2, next_row_calculation   # Se todas as colunas de B foram processadas, ir para a próxima linha de A

    # Inicializar o produto para o elemento [t3][t4]
    li $t8, 0

    # Multiplicar a linha t3 de A pela coluna t4 de B
    li $t5, 0  # $t5 = índice da coluna da linha t3 de A
    li $t6, 0  # $t6 = índice da linha da coluna t4 de B

inner_product_loop:
    lw $t7, ($t0)  # Carregar o elemento de A na linha t3 e coluna t5
    lw $t9, ($t1)  # Carregar o elemento de B na linha t6 e coluna t4
    mul $t7, $t7, $t9  # Multiplicar os elementos
    add $t8, $t8, $t7  # Adicionar o produto ao acumulador
    addi $t0, $t0, 4  # Avançar para o próximo elemento na linha de A
    addi $t1, $t1, 8  # Avançar para o próximo elemento na coluna de B
    addi $t5, $t5, 1  # Avançar para a próxima coluna na linha de A
    bne $t5, 2, inner_product_loop  # Se não todas as colunas de A foram processadas, continuar

    # Armazenar o produto na matriz resultado
    sw $t8, ($t2)  # Armazenar o produto no endereço correspondente na matriz resultado
    addi $t2, $t2, 4  # Avançar para o próximo elemento na matriz resultado

    # Avançar para a próxima coluna de B
    addi $t1, $t1, -8  # Resetar o ponteiro para a coluna de B
    addi $t1, $t1, 4   # Avançar para a próxima coluna de B

    addi $t4, $t4, 1  # Avançar para a próxima coluna de B
    j calculate_column_loop  # Processar a próxima coluna de B

next_row_calculation:
    # Avançar para a próxima linha de A
    addi $t3, $t3, 1  # Avançar para a próxima linha de A
    j calculate_product_loop  # Processar a próxima linha de A

print_result:
    # Imprimir a matriz resultado
    la $t2, resultado   # $t2 = endereço da matriz resultado
    li $t3, 0  # $t3 = índice da linha da matriz resultado

print_row_loop:
    beq $t3, 3, exit_program  # Se todas as linhas da matriz resultado foram impressas, sair

    # Imprimir os elementos da linha atual da matriz resultado
    li $t4, 0  # $t4 = índice da coluna da matriz resultado

print_column_loop:
    beq $t4, 2, next_row_print   # Se todas as colunas da linha atual foram impressas, ir para a próxima linha

    # Imprimir o elemento atual da matriz resultado
    lw $a0, ($t2)   # Carregar o elemento atual da matriz resultado
    li $v0, 1   # syscall para imprimir inteiro
    syscall
    li $a0, ' '   # Imprimir espaço
    li $v0, 11   # syscall para imprimir caractere
    syscall

    # Avançar para o próximo elemento na linha da matriz resultado
    addi $t2, $t2, 4

    addi $t4, $t4, 1  # Avançar para a próxima coluna da matriz resultado
    j print_column_loop  # Processar o próximo elemento da linha da matriz resultado

next_row_print:
    # Imprimir uma nova linha
    li $a0, '\n'   # Imprimir nova linha
    li $v0, 11   # syscall para imprimir caractere
    syscall

    # Avançar para a próxima linha da matriz resultado
    addi $t3, $t3, 1
    j print_row_loop  # Processar a próxima linha da matriz resultado

exit_program:
    # Encerrar o programa
    li $v0, 10
    syscall
