.data
	Mat: .space 64
	Mat2: .space 64
	.align 2
	Ent1: .asciiz "Insira do valor de Mat["
	Ent2: .asciiz "]["
	Ent3: .asciiz "]:"
	QuantIguais: .asciiz "Quantidade de iguais:"
	somaIJ: .asciiz "\nSoma posicoes: "
	primeira: .asciiz "MATRIZ 1:"
	segunda: .asciiz "MATRIZ 2:"
.text
main:
	#================ MATRIZ ======================
	la $a0, Mat # a0 fica com o endereco da primeira matriz
	la $a1, Mat2 # a1 fica com o endereco da segunda matriz
	li $s0, 3 # a1 = 4 (linhas da matriz)
	li $s1, 3 # a2 = 4 (colunas da matriz)
	
	jal leitura # (mat, nlin,ncol) Leitura da primeira matriz
	move $a0, $a1 # Endereco da segunda matriz em a0
	move $a1, $v0 # Endereco da primeira matriz em a1
	
	jal leitura # Le a segunda matriz
	move $a0, $a1 # Endereco da primeira matriz volta pra a0
	move $a1, $v0 # Endereco da segunda matriz volta pra a1
	# a0 = mat  e  a1 = mat2
	jal iguais
	
	la $a0, QuantIguais # Move o texto
	li $v0, 4 # Codigo para imprimir string
	syscall
	
	move $a0, $s3 # Move a quantidade de iguais
	li $v0, 1 # Codigo para imprimir inteiro
	syscall
	
	la $a0, somaIJ # Move o texto
	li $v0, 4 # Codigo para imprimir string
	syscall
	
	move $a0, $s4 # Move a quantidade de iguais
	li $v0, 1 # Codigo para imprimir inteiro
	syscall
	

fim:
	li $v0, 10 # Codigo para finalizar programa
	syscall # Finaliza programa
	
indice:
	mul $v0, $t0, $s1 # i * ncol
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
	blt $t1, $s1, l # if (v < ncol) goto l
	li $t1, 0 # j = 0
	addi $t0, $t0, 1 # i++
	blt $t0, $s0, l # if( i < nlin ) goto l
	li $t0, 0 # i = 0
	lw $ra, ($sp) # Recupera o retorno para main
	addi $sp, $sp, 4 # Libera espaco na pilha
	
	move $v0, $a3 # Endereco base da matriz para retorno
	jr $ra # Retorna

iguais:
	subi $sp, $sp, 4 # Espaco para 1 item na pilha
	sw $ra, ($sp) # Salva retorno para main
	li $s3, 0 # Quantidade de iguais
	li $s4, 0 # Soma de i+j
	move $a3, $a0 # a3 é o endereco da primeira matriz
	move $a2, $a1 # a2 é o endereco da segunda matriz
	
ig:
	jal indice # Calcula endereco de mat1 [i][j]
	lw $t8, ($v0) # Carrega elemento da matriz
	move $a1, $a3 # a1 recebe o endereco da primeira matriz

	move $a3, $a2 # a3 recebe o endereco da segunda matriz
	jal indice # Calcula endereco de mat2 [i][j]
	lw $t9, ($v0) # Carrega elemento da matriz
	move $a3, $a1 # a3 recebe o endereco da primeira matriz
	#t8 é o elemento [i][j] da primeira matriz e t9 da segunda
	
	bne $t8, $t9, pula
	addi $s3, $s3, 1 # Soma 1 na quantidade de iguais
	add $s4, $s4, $t0 # Soma i na soma
	add $s4, $s4, $t1 # Soma j na soma
pula:	
	addi $t1, $t1, 1 # j++
	blt $t1, $s1, ig # if( j < ncol ) goto e
	li $t1, 0 # j = 0
	addi $t0, $t0, 1 # i ++
	blt $t0, $s0, ig # if( i < nlin ) goto e
	li $t0, 0  # i = 0
	lw $ra, ($sp) # Recupera o retorno para main
	addi $sp, $sp, 4 # Libera o espaco na pilha
	jr $ra # Retorno para main
