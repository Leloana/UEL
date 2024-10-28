.data
	tamanho: .asciiz "Insira o tamanho do vetor: "
	ent: .asciiz "Insira o valor de Vet["
	ent2: .asciiz "]: "
	vetA: .asciiz "VetA = "
	greater: .asciiz "\nValor maior elemento = "
	greaterPosic: .asciiz "\nPosicao maior elemento = "
	smaller: .asciiz "\nValor menor elemento = "
	smallerPosic: .asciiz "\nPosicao menor elemento = "
.text

main:
	#	$s0 = n
	#	$s1 = Tamanho em bits
	#	$a1 = VetorA
	li $v0, 4 # Codigo para escrever string
	la $a0, tamanho # Carrega a string a ser escrita
	syscall # Escreve String
	li $v0, 5 # Codigo para ler inteiro
	syscall
	move $s0, $v0 # Armazena input no endereço $s0
	li $t0, 4
	mult $s0, $t0 # Multiplica n por 4 ( tamanho do inteiro )
	mflo $s1 # Guarda o resultado em s1
	move $a0, $s1 # Tamanho do vetor
	li $v0, 9 # Sinaliza pra alocar memoria
	syscall # Aloca memoria
	move $a1, $v0 # Guarda o endereco alocado em a1
	move $a0, $a1 # Move o endereco do primeiro vetor para a0
	jal leitura # Le o vetA
	move $a1, $v0 # Armazena vetA em a1
	li $v0, 4 # Texto para sinalizar a impressao do primeiro vetor
	la $a0, vetA
	syscall	
	move $a0, $a1 # Move o endereco do primeiro vetor para a0
	jal escrita # Escreve o primeiro vetor
	move $a1, $v0 
	jal maiorMenor
fim:
	li $v0, 10 # Finaliza codigo
	syscall
	
leitura:
	move $t0, $a0 #Armazena o endereço do vetor em $t0
	move $t1, $t0 #Armazena o endereço do vetor em $t1
	li $t2, 0 #Inicia contador "i = 0"
loop:
	la $a0, ent #Carrega String "Insira o valor de Vet["
	li $v0, 4
	syscall #Escreve String
	move $a0, $t2 #Carrega indice do elemento atual do vetor
	li $v0, 1 #Codigo para imprimir inteiro
	syscall #Imprime inteiro
	
	la $a0, ent2 #Carrega String "]: "
	li $v0, 4
	syscall #Escreve String
	
	li $v0, 5 #Codigo para ler inteiro
	syscall #Le input do teclado(inteiro)
	sw $v0, 0($t1) #Armazena input no endereço $t1 do vetor
	
	add $t1, $t1, 4 #Vai para proximo endereço do vetor (4 pois é o tamanho de um inteiro)
	addi $t2, $t2, 1 #Adiciona 1 no contador "i ++"
	blt $t2, $s0, loop  #Se i < $s0
	move $v0, $t0 #Endereço de vet para retorno
	jr $ra 

escrita:
	move $t0, $a0 #Armazena o endereço do vetor em $t0
	move $t1, $t0 #Armazena o endereço do vetor em $t1
	li $t2, 0 #Inicia contador "i = 0"
e:
	lw $a0, 0($t1) #Carrega elemento de endereço $t1 em $a0
	li $v0, 1 #Codigo para escrever inteiro
	syscall #Escreve inteiro
	li $a0, 32 #Codigo para escrever " " (espaço)
	li $v0, 11
	syscall #Escreve " " 
	addi $t1, $t1, 4 #Vai para proximo endereço do vetor (4 pois é o tamanho de um inteiro)
	addi $t2, $t2, 1 #Adiciona 1 no contador "i ++"
	blt $t2, $s0, e #Se i < $s0
	move $v0, $t0 #Endereço de vet para retorno
	jr $ra
	
maiorMenor:
	move $t0, $a1 # Armazena o endereco do vetor em $t0
	li $t1, 0 # Inicia contador
	li $t2, -2147483647 # Maior numero
	li $t3, 0 # Posicao do maior numero
	li $t4, 2147483647 # Menor numero
	li $t5, 0 # Posicao do menor numero
mm:
	lw $t6, 0($t0) #Carrega elemento de endereço $t1 em $a0
	bgt $t6, $t2, maior # if( atual > maior) goto maior
	blt $t6, $t4, menor # if( atual < menor) goto me
menor:
	bgt $t6, $t4, cont # if( atual > menor) goto cont
	move $t4, $t6 # Move o valor do menor para t4
	move $t5, $t1 # Move a posicao do menor para t5
	j cont
maior:
	move $t2, $t6 # Move o valor do maior para t2
	move $t3, $t1 # Move a posicao do maior para t3
	j menor
cont:
	addi $t0, $t0, 4 # Soma 4 no contador para percorrer o vetor
	addi $t1, $t1, 1 # Soma 1 no contador usado como flag de parada
	blt $t1, $s0 mm # Volta para inicio do loop
	#===================INFOS MAIOR===============================
	la $a0, greater # Carrega o texto de maior
	li $v0, 4
	syscall # Escreve
	move $a0, $t2 # Carrega o valor do maior
	li $v0, 1 
	syscall # Escreve o valor do maior
	la $a0, greaterPosic # Carrega texto da posicao do maior
	li $v0, 4
	syscall # Escreve
	addi $t3, $t3, 1 # Soma 1 na posic pois a posicao inicial = 1 
	move $a0, $t3 # Carrega a posicao do maior
	li $v0, 1
	syscall # Escreve a posicao
	#===================INFOS MENOR===============================
	la $a0, smaller # Carrega o texto de menor
	li $v0, 4
	syscall # Escreve 
	move $a0, $t4 # Carrega o valor do menor
	li $v0, 1
	syscall # Escreve o valor do menor
	la $a0, smallerPosic # Carrega o texto da posicao do menor
	li $v0, 4
	syscall # Escreve
	addi $t5, $t5, 1 # Soma 1 na posic pois a posicao inicial = 1 
	move $a0, $t5 # Carrega a posicao do menor
	li $v0, 1
	syscall # Escreve a posicao

	jr $ra # Retorna
	
	
	