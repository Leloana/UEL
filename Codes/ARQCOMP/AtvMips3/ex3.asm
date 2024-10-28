.data
	Mat: .space 64
	.align 2
	Ent1: .asciiz "Insira do valor de Mat["
	Ent2: .asciiz "]["
	Ent3: .asciiz "]:"
	linNULL: .asciiz "Linhas nulas: "
	colNULL: .asciiz "\nColunas nulas: "
	
.text
main:
	#================ MATRIZ ======================
	la $a0, Mat # a0 fica com o endereco da matriz
	li $a1, 4 # a1 = 4 (linhas da matriz)
	li $a2, 4 # a2 = 4 (colunas da matriz)
	jal leitura # (mat, nlin,ncol)
	move $a0, $v0
	jal escrita # (mat, lin , col)
	move $a0, $v0
	jal colunasNull # (mat, lin , col)
	move $a0, $v0
	jal linhasNull # (mat, lin , col)
	#============== RESULTADOS =====================
	la $a0, linNULL # Carrega texto de linhas nulas
	li $v0, 4 # Codigo de imprimir string
	syscall
	move $a0, $s0 # Move a quantidade de linhas nulas para a0
	li $v0, 1 # Codigo para imprimir um inteiro
	syscall
	la $a0, colNULL # Carrega o texto de colunas nulas
	li $v0, 4 # Codigo de imprimir string
	syscall
	move $a0, $s1 # Move a quantidade de colunas nulas para a0
	li $v0, 1 # Codigo para imprimir um inteiro
	syscall
	
	li $v0, 10 # Codigo para finalizar programa
	syscall # Finaliza programa
	
indice:
	mul $v0, $t0, $a2 # i * ncol
	add $v0, $v0, $t1 # (i * ncol) + j
	sll $v0, $v0, 2 # [(i *ncol) + j] * 4 (inteiro)
	add $v0, $v0, $a3 # Soma o endereço base de mat
	jr $ra # Retorna

leitura:
	subi $sp, $sp, 4 # Espaco para 1 item na pilha
	sw $ra, ($sp) # Salva o retorno para a main
	move $a3, $a0 # aux = endereco base de mat
	li $t0, 0
	li $t1, 0
l:
	la $a0, Ent1 # Carrega endereco da string
	li $v0,4 # Codigo de impressao de string
	syscall # Imprime string
	
	move $a0, $t0 # Valor de i para impressao
	li $v0, 1 # Codigo de impressao de inteiro
	syscall # Imprime i
	
	la $a0, Ent2 # Carrega endereco da string
	li $v0, 4 # Codigo de impressao de string
	syscall # Imprime a string
	
	move $a0, $t1 # Valor de j para impressao
	li $v0, 1 # Codigo de impressao de inteiro
	syscall # Imprime j
	
	la $a0, Ent3
	li $v0, 4 # Codigo de impressao de string
	syscall # Imprime a string
	
	li $v0, 5 # Codigo de leitura de inteiro
	syscall # Leitura do valor ( retorna em v0 )
	move $t2, $v0 # aux = valor lido
	
	jal indice # Calcula o endereco de mat [i][j]
	sw $t2, ($v0) # mat[i][j] = aux
	
	addi $t1, $t1, 1 # j++
	blt $t1, $a2, l # if (v < ncol) goto l
	li $t1, 0 # j = 0
	addi $t0, $t0, 1 # i++
	blt $t0, $a1, l # if( i < nlin ) goto l
	li $t0, 0 # i = 0
	lw $ra, ($sp) # Recupera o retorno para main
	addi $sp, $sp, 4 # Libera espaco na pilha
	
	move $v0, $a3 # Endereco base da matriz para retorno
	jr $ra # Retorna

escrita:
	subi $sp, $sp, 4 # Espaco para 1 item na pilha
	sw $ra, ($sp) # Salva retorno para main
	move $a3, $a0 # aux = endereco base de mat
e:
	jal indice # Calcula endereco de mat [i][j]
	lw $a0, ($v0) # Carrega elemento da matriz
	li $v0, 1 # Codigo para imprimir um inteiro
	syscall

	la $a0, 32 # Codigo ASCII para espaco
	li $v0, 11 # Codigo para impressao de caracter
	syscall # Imprime espaco
	
	addi $t1, $t1, 1 # j++
	blt $t1, $a2, e # if( j < ncol ) goto e
	la $a0, 10 # Codigo ASCII para newline
	syscall # Pula a linha 	
	li $t1, 0 # j = 0
	addi $t0, $t0, 1 # i ++
	blt $t0, $a1, e # if( i < nlin ) goto e
	li $t0, 0  # i = 0
	lw $ra, ($sp) # Recupera o retorno para main
	addi $sp, $sp, 4 # Libera o espaco na pilha
	move $v0, $a3 # Endereco base da matriz para retorno
	jr $ra # Retorno para main
	
linhasNull:
	subi $sp, $sp, 4 # Espaco para 1 item na pilha
	sw $ra, ($sp) # Salva retorno para main
	move $a3, $a0 # aux = endereco base de mat
	# Inicializa a soma de cada fileira
	li $t2, 0 # Soma das linhas
	li $s0, 0 # Quantidade de linhas nulas
lin:
	jal indice # Calcula endereco de mat [i][j]
	lw $t8, ($v0) # Carrega elemento da matriz
	add $t2, $t2, $t8 # Soma o elemento atual na soma
	addi $t1, $t1, 1 # j++
	blt $t1, $a2, lin # if( j < ncol ) goto e
	li $t1, 0 # j = 0
	bnez $t2, linNotNull # Se a soma da linha for igual a zero 
	addi $s0, $s0, 1 # Soma das linhas nulas ++
linNotNull:
	li $t2, 0 # Zera a soma da coluna
	addi $t0, $t0, 1 # i ++
	blt $t0, $a1, lin # if( i < nlin ) goto e
	li $t0, 0  # i = 0
	lw $ra, ($sp) # Recupera o retorno para main
	addi $sp, $sp, 4 # Libera o espaco na pilha
	move $v0, $a3 # Endereco base da matriz para retorno
	jr $ra # Retorno para main

colunasNull:
	subi $sp, $sp, 4 # Espaco para 1 item na pilha
	sw $ra, ($sp) # Salva retorno para main
	move $a3, $a0 # aux = endereco base de mat
	# Inicializa a soma de cada fileira
	li $t2, 0 # Soma das colunas
	li $s1, 0 # Quantidade de colunas nulas
c:
	jal indice # Calcula endereco de mat [i][j]
	lw $t8, ($v0) # Carrega elemento da matriz
	add $t2, $t2, $t8 # Soma o elemento atual na soma	
	addi $t0, $t0, 1 # j++
	blt $t0, $a2, c # if( j < ncol ) goto e	
	li $t0, 0 # j = 0
	bnez $t2, colNotNull # Se a soma da coluna for igual a zero 
	addi $s1, $s1, 1 # Soma das colunas nulas ++
colNotNull:
	li $t2, 0 # Zera a soma da coluna
	addi $t1, $t1, 1 # i ++
	blt $t1, $a1, c # if( i < nlin ) goto e
	li $t1, 0  # i = 0
	lw $ra, ($sp) # Recupera o retorno para main
	addi $sp, $sp, 4 # Libera o espaco na pilha
	move $v0, $a3 # Endereco base da matriz para retorno
	jr $ra # Retorno para main

