.data
	Mat: .space 64
	.align 2
	Ent1: .asciiz "Insira do valor de Mat["
	Ent2: .asciiz "]["
	Ent3: .asciiz "]:"
	abaixoPrinc: .asciiz "\nSoma abaixo da princial: "
	acimaPrinc: .asciiz "\nSoma acima da princial: "
	maiorAcima: .asciiz "\nMaior valor acima da principal: "
	menorAbaixo: .asciiz "\nMenor valor abaixo da principal: "
	diff: .asciiz "\nsomaAcima - somaAbaixo = "
	
.text
main:
	#================ MATRIZ ======================
	la $a0, Mat # a0 fica com o endereco da matriz
	li $a1, 4 # a1 = 4 (linhas da matriz)
	li $a2, 4 # a2 = 4 (colunas da matriz)
	jal leitura # (mat, nlin,ncol)
	move $a0, $v0
	jal principal # (mat, lin , col)
	move $a0, $v0
	jal escrita
	move $t5, $v0
	#================= RESULTADOS ===================
	la $a0, acimaPrinc # Move o texto
	li $v0, 4  # Codigo para imprimir string
	syscall
	move $a0, $s0 # Soma acima da principal
	li $v0, 1 # Codigo para imprimir inteiro
	syscall
	
	la $a0, abaixoPrinc # Move o texto
	li $v0, 4 # Codigo para imprimir string
	syscall
	move $a0, $s1 # Soma abaixo da principal
	li $v0, 1 # Codigo para imprimir inteiro
	syscall
	
	la $a0, diff # Move o texto
	li $v0, 4 # Codigo para imprimir string
	syscall
	sub $t9, $s0, $s1
	move $a0, $t9 # Menor valor abaixo da principal
	li $v0, 1 # Codigo para imprimir inteiro
	syscall
	
	la $a0, maiorAcima # Move o texto
	li $v0, 4 # Codigo para imprimir string
	syscall
	move $a0, $s2 # Maior valor acima da principal
	li $v0, 1 # Codigo para imprimir inteiro
	syscall
	
	la $a0, menorAbaixo # Move o texto
	li $v0, 4 # Codigo para imprimir string
	syscall
	move $a0, $s3 # Menor valor abaixo da principal
	li $v0, 1 # Codigo para imprimir inteiro
	syscall
	
	move $a0, $t5			# Endere�o de Mat
	jal crescente
	move $a0, $v0
	jal escrita
	
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

principal:
	subi $sp, $sp, 4 # Espaco para 1 item na pilha
	sw $ra, ($sp) # Salva retorno para main
	move $a3, $a0 # aux = endereco base de mat
	li $s0, 0 # Soma acima da principal
	li $s1, 0 # Soma abaixo da principal
	li $s2, -2147483647 # Maior acima
	li $s3,  2147483647 # Menor abaixo
prin:
	jal indice # Calcula endereco de mat [i][j]
	lw $t2, ($v0) # Carrega elemento da matriz
	beq $t0, $t1 continua
	bgt $t0, $t1, baixo # if (i < j) esta abaixo da diagonal principal
	
cima:
	add $s0, $s0, $t2 # Soma o elemento acima da diagonal
	blt $t2, $s2, continua # Se t2 < s2 continua 
	move $s2, $t2 # senao s2 = t2
	j continua
baixo:
	add $s1, $s1, $t2 # Soma o elemento abaixo da diagonal
	bgt $t2, $s3, continua # Se t2 > s3 continua
	move $s3, $t2 # Senao s3 = t2
continua:
	addi $t1, $t1, 1 # j++
	blt $t1, $a2, prin # if( j < ncol ) goto e 	
	li $t1, 0 # j = 0
	addi $t0, $t0, 1 # i ++
	blt $t0, $a1, prin # if( i < nlin ) goto e
	li $t0, 0  # i = 0
	lw $ra, ($sp) # Recupera o retorno para main
	addi $sp, $sp, 4 # Libera o espaco na pilha
	move $v0, $a3 # Endereco base da matriz para retorno
	jr $ra # Retorno para main
	
crescente:
	move $t3, $a0 # t3 recebe endereco da matriz
	move $t4, $t3 # Ponteiro para elemento atual
	move $t7, $t3 # Ponteiro para proximo elemento
	li $t2, 0 # Contador
	
	mult $a1,$a2 # Multiplica dimensoes na matriz para saber quantia de valroes
	mflo $t5 # Armazena em t5 (bubble sort deve analisar todos os valores
	subi $t5 ,$t5 ,1 # Subtrai 1 pois inicia em zero
	li $t6, 0 #Contador
cres:
	lw $t8, ($t7) # elemento atual
	lw $t9, 4($t4) # proximo elemento
	bgt $t8, $t9, trocaPosicao # if (Mat[i][j] > Mat[i+1][j]) troca a posicao
		
loop:
	addi $t4, $t4, 4	# Mat[i+1][j]
	addi $t2, $t2, 1 # i++
	blt $t2, $t5, cres# if (i < 15) goto loop
	addi $t6, $t6, 4 # $t6 += 4
	subi $t5, $t5, 1 # $t5 -= 1 subtrai no contador
	li $t2, 0 # i = 0
	move $t4, $t3	# Endereco base de Mat
	add $t4, $t4, $t6# Endereco de Mat[i+1][j]
	addi $t7, $t7, 4	# Endereco += 4
	bnez $t5, cres # if ($t5 < 0) goto loop
	move $v0, $t3	# Endereco de retorno de Mat
	jr $ra	# Retorno para a main	
	
trocaPosicao:
	sw $t9, 0($t7) # Mat[i][j] = menor
	sw $t8, 4($t4) # Mat[i+1][j] = maior
	j loop # goto l2

escrita:
	subi $sp, $sp, 4 # Espaco para 1 item na pilha
	sw $ra, ($sp) # Salva retorno para main
	move $a3, $a0 # aux = endereco base de mat
	
	la $a0, 10 # Codigo ASCII para newline
	li $v0, 11 # Codigo para impressao de caracter
	syscall # Pula a linha 	
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
