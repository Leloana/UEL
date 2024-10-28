# MARCELO FERREIRA DE ALMEIDA

.data
	matriz_A:   .word 1, 2, 3        # Linha 1 da matriz
            .word 4, 5, 6        # Linha 2 da matriz
	vetor_V:    .word 1, 2, 3        # Vetor V
	resultado:  .space 8             # Espaço para armazenar o resultado

.text
main:
    la $t0, matriz_A # t0 recebe matriz a
    la $t1, vetor_V # t1 recebe vetor v
    la $t2, resultado # t2 recebe resultado
    li $t3, 0 # seta t3 como zero
    li $t4, 0# seta t4 como zero
    li $t5, 0# seta t5 como zero
outer_loop:
    beq $t3, 2, done_outer_loop # Verificar se todas as linhas da matriz foram processadas
    
    li $t4, 0 # Reinicializar o índice de coluna da matriz
    li $t5, 0# Reinicializar o produto atual
inner_loop:
    beq $t4, 2, done_inner_loop     # Verificar se todas as colunas da matriz foram processadas 
    lw $t6, 0($t0)# Carregar o elemento atual da matriz
    lw $t7, 0($t1)# Carregar o elemento atual do vetor
    mul $t6, $t6, $t7 # Multiplicar o elemento da matriz pelo elemento correspondente do vetor
    add $t5, $t5, $t6# Adicionar o resultado ao produto atual
    addi $t0, $t0, 4# Avançar para o próximo elemento da linha da matriz
    addi $t4, $t4, 1# Avançar para a próxima coluna da matriz e do vetor
    addi $t1, $t1, 4
    j inner_loop

done_inner_loop:   
    sw $t5, 0($t2)# Armazenar o produto atual no vetor resultado
    addi $t3, $t3, 1# Avançar para a próxima linha da matriz
    addi $t2, $t2, 4# Avançar para o próximo elemento do vetor
    li $t4, 0# Avançar para a próxima linha da matriz e reinicializar o índice de coluna
    li $t5, 0
    j outer_loop
done_outer_loop:  
    la $t2, resultado# Imprimir o vetor resultado
    li $t3, 0 
print_loop:
    beq $t3, 2, exit_print_loop
    lw $a0, 0($t2)
    li $v0, 1
    syscall
    li $a0, ' '
    li $v0, 11
    syscall
    addi $t2, $t2, 4
    addi $t3, $t3, 1
    j print_loop
exit_print_loop:
    
    li $v0, 10# Encerrar o programa
    syscall
