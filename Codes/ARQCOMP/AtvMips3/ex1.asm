.data
	Mat: .space 48
	Ent1: .asciiz "Insira do valor de Mat["
	Ent2: .asciiz "]["
	Ent3: .asciiz "]:"
	
	.align 2
	vet: .space 12 # reserva espaco para 3 inteiros (3 * 4 bytes)
	msg1: .asciiz "Digite vetor["
	msg2: .asciiz "]: "
.text
main:
	#================== VETOR ====================
	la $v0, vet #Armazena endereço do vetor
	move $a0, $v0
	jal lervet #Funcao de leitura
	move $t8, $v0 # t8 fica com o endereco do vetor
	
	#================ MATRIZ ======================
	
	la $a0, Mat # a0 fica com o endereco da matriz
	li $a1, 4 # a1 = 4 (linhas da matriz)
	li $a2, 3 # a2 = 3 (colunas da matriz)
	jal leitura # (mat, nlin,ncol)
	move $a0, $v0
	move $a3, $t8
	jal multiplica # (mat, lin , col, vet)
	
	li $v0, 10 # Codigo para finalizar programa
	syscall # Finaliza programa
	
	
lervet:
	move $t0, $a0 #Armazena o endereço do vetor em $t0
	move $t1, $t0 #Armazena o endereço do vetor em $t1
	li $t2, 0 #Inicia contador "i = 0"
loopvet:
	la $a0, msg1 #Carrega String "Digite vetor["
	li $v0, 4
	syscall #Escreve String
	move $a0, $t2 #Carrega indice do elemento atual do vetor
	li $v0, 1 #Codigo para imprimir inteiro
	syscall #Imprime inteiro
	
	la $a0, msg2 #Carrega String "]: "
	li $v0, 4
	syscall #Escreve String
	
	li $v0, 5 #Codigo para ler inteiro
	syscall #Le input do teclado(inteiro)
	sw $v0, ($t1) #Armazena input no endereço $t1 do vetor
	
	add $t1, $t1, 4 #Vai para proximo endereço do vetor (4 pois é o tamanho de um inteiro)
	addi $t2, $t2, 1 #Adiciona 1 no contador "i ++"
	blt $t2, 3, loopvet  #Se i < 3 continua loop
	move $v0, $t0 #Endereço de vet para retorno
	jr $ra 

	
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
	
multiplica:
	subi $sp, $sp, 4 # Espaco para 1 item na pilha
	sw $ra, ($sp) # Salva retorno para main
	move $t5, $a3 # Guarda o endereco do vetor em $t5
	li $t6, 0
	add $t6, $t6, $t5 # Guarda o endereco base do vetor em $t5
	move $a3, $a0 # aux = endereco base de mat
e:
	jal indice # Calcula endereco de mat [i][j]
	lw $t7, ($v0) # Armazena numero atual da matriz
	lw $t8, 0($t5) # Armazena numero atual do vetor
	
	mult $t7, $t8 # Multiplica matriz x vetor
	
	mflo $t9 # Resultado multiplicacao
	
	move $a0, $t9
	li $v0, 1 # Codigo para imprimir inteiro
	syscall # Imprime mat[i][j]
	
	la $a0, 32 # Codigo ASCII para espaco
	li $v0, 11 # Codigo para impressao de caracter
	syscall # Imprime espaco
	
	addi $t5, $t5, 4 # j++
	addi $t1, $t1, 1 # j++
	blt $t1, $a2, e # if( j < ncol ) goto e 
	
	la $a0, 10 # Codigo ASCII para newline
	syscall # Pula a linha
	
	li $t1, 0 # j = 0
	addi $t0, $t0, 1 # i ++
	li $t5, 0
	add $t5, $t5, $t6 # Guarda o endereco do vetor em $t5
	
	blt $t0, $a1, e # if( i < nlin ) goto e
	li $t0, 0  # i = 0
	lw $ra, ($sp) # Recupera o retorno para main
	addi $sp, $sp, 4 # Libera o espaco na pilha
	
	move $v0, $a3 # Endereco base da matriz para retorno
	jr $ra # Retorno para main
	