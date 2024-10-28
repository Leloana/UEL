.data
	Mat: .space 36
	.align 2
	Ent1: .asciiz "Insira do valor de Mat["
	Ent2: .asciiz "]["
	Ent3: .asciiz "]:"
	saidaTrue: .asciiz "A é matriz de permutacao"
	saidaFalse: .asciiz "A nao é matriz de permutacao"
	
.text
main:
	#================ MATRIZ ======================
	
	la $a0, Mat # a0 fica com o endereco da matriz
	li $a1, 3 # a1 = 4 (linhas da matriz)
	li $a2, 3 # a2 = 3 (colunas da matriz)
	jal leitura # (mat, nlin,ncol)
	move $a0, $v0
	jal escrita # (mat, lin , col, vet)
	
	beqz $v0, false
	li $v0, 4
	la $a0, saidaTrue
	syscall
	j fim
false:
	li $v0, 4
	la $a0, saidaFalse
	syscall
fim:
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
	li $t8, 0 # Soma das linhas 
	li $t9, 1 # Auxiliar
e:
	jal indice # Calcula endereco de mat [i][j]
	lw $t7, ($v0) # Armazena numero atual da matriz
	
	bltz $t7, notP
	
	add $t8, $t8, $t7
	
	addi $t1, $t1, 1 # j++
	blt $t1, $a2, e # if( j < ncol ) goto e 
	
	li $t1, 0 # j = 0
	
	bne $t8, $t9, notP
	
	addi $t9,$t9, 1
	addi $t0, $t0, 1 # i ++
	blt $t0, $a1, e # if( i < nlin ) goto e
	li $t0, 0  # i = 0
P:
	li $v0, 1 # 1 é true
	j return
notP:
	li $v0, 0 # 0 é false
return:
	lw $ra, ($sp) # Recupera o retorno para main
	addi $sp, $sp, 4 # Libera o espaco na pilha
	jr $ra # Retorno para main
