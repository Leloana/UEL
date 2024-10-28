.data
	tamanho: .asciiz "Insira o tamanho do vetor: "
	ent: .asciiz "Insira o valor de Vet["
	ent2: .asciiz "]: "
	vetA: .asciiz "VetA = "
	vetB: .asciiz "\nVetB = "
	first: .asciiz "Insira o primeiro vetor:\n"
	second: .asciiz "Insira o segundo vetor:\n"
	subtracao: .asciiz "\nVetA[pares] - VetB[impares] =  " 
.text

main:
	#	$s0 = n
	#	$s1 = Tamanho em bits
	#	$a1 = VetorA
	#	$a2 = VetorB
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
	
	li $v0, 4 # Texto para sinalizar a insercao do primeiro vetor
	la $a0, first
	syscall
	
	move $a0, $a1 # Move o endereco do primeiro vetor para a0
	jal leitura # Le o vetA
	move $a1, $v0 # Armazena vetA em a1
	
	move $a0, $s1 # Tamanho do vetor
	li $v0, 9 # Sinaliza pra alocar memoria
	syscall # Aloca memoria
	move $a2, $v0 # Guarda o endereco alocado em a1
	
	li $v0, 4 # Texto para sinalizar a insercao do segundo vetor
	la $a0, second
	syscall
	
	move $a0, $a2 # Move o endereco do segundo vetor para a0
	jal leitura # Le o vetA
	move $a2, $v0 # Armazena vetB em a0
	
	li $v0, 4 # Texto para sinalizar a impressao do primeiro vetor
	la $a0, vetA
	syscall
	
	move $a0, $a1 # Move o endereco do primeiro vetor para a0
	jal escrita # Escreve o primeiro vetor
	move $a1, $v0 
	
	li $v0, 4 # Texto para sinalizar a impressao do segundo vetor
	la $a0, vetB
	syscall
	
	move $a0, $a2 # Move o endereco do segundo vetor para a0
	jal escrita # Escreve o segundo vetor
	move $a2, $v0
	
	la $a0, subtracao #Texto VetA[pares] - VetB[impares]
	li $v0, 4
	syscall
	
	jal diferenca# Funcao que subtrai os elementos de posicao
	# Par de VetA dos elementos de posicoes impares de VetB
	move $a0, $v0 # Move o resultado da funcao para a0
	li $v0, 1
	syscall # Escreve o resultado da funcao
	
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
	
diferenca:
	move $t0, $a1 # Armazena o endereço do vetor a1 em $t0
	move $t1, $a2 # Armazena o endereço do vetor a2 em $t0
	li $t2, 0  # Inicia contador "i = 0"
	li $t9, 0  # Soma dos pares
	li $t8, 0 # Soma dos impares
	li $t7, 2
d:
	lw $t3, 0($t0) # Carrega elemento do primeiro vetor
	lw $t4, 0($t1) # Carrega elemento do segundo vetor
	
	div $t2, $t7 # Divide o valor atual de i por dois
	mfhi $t6 # Guarda o resto em t6
	
	beqz $t6, pula # Se o resto for = 0 o numero é par senao é impar
	add $t8, $t8,$t4 # Soma posicao impar do VetB
	j con
pula:
	add $t9, $t9,$t3 # Soma posicao par do VetA
con:
	addi $t1, $t1, 4 #Vai para proximo endereço do vetor (4 pois é o tamanho de um inteiro)
	addi $t0, $t0, 4 #Vai para proximo endereço do vetor (4 pois é o tamanho de um inteiro)
	addi $t2, $t2, 1 #Adiciona 1 no contador "i ++"
	blt $t2, $s0, d #Se i < $s0
	
	sub $v0, $t9, $t8 # v0 retorna a subtracao de pares VetA - impares VetB
	jr $ra