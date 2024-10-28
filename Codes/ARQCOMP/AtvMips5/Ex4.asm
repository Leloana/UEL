.data
	tamanho: .asciiz "Insira o tamanho do vetor: "
	ent: .asciiz "Insira o valor de Vet["
	ent2: .asciiz "]: "
	vetA: .asciiz "Vetcomp = "
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
	jal compact
	move $a0, $v0
	jal escrita

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
	
compact:
	move $t0, $a0 #Armazena o endereço do vetor em $t0
	move $t1, $t0 #Armazena o endereço do vetor em $t1
	li $t2, 0 #Inicia contador "i = 0"
	li $t4, 0 # Inicia a auxiliar que vai percorrer o vetor novamente
	li $t5, 0 # Inicia a auxiliar que vai  percorrer o vetor junto do t4
	li $t6, 0 # Guarda valor do contador
c:
	lw $t3, 0($t1) #Carrega elemento de endereço $t1 em $a0
	bnez $t3, con
inicia:
	move $t4, $t1 # t4 guarda a posicao atual do vetor
	move $t5, $t1 # t4 guarda a posicao atual do vetor
	move $t6, $t2
	sub $s0, $s0, 1 # Diminui 1 no tamanho do vetor
i:
	lw $t7, 4($t4)
	sw $t7,0($t5)
	
	addi $t4, $t4, 4 # Vai ao proximo elemento
	addi $t5, $t5, 4 # Vai ao proximo elemento
	addi $t6, $t6, 1 # Adiciona 1 no contador
	blt $t6, $s0, i #Se i < $s0
	move $t1, $t0 # Reseta contadores
	li $t2, 0
	j c
con:
	addi $t1, $t1, 4 #Vai para proximo endereço do vetor (4 pois é o tamanho de um inteiro)
	addi $t2, $t2, 1 #Adiciona 1 no contador "i ++"
	blt $t2, $s0, c #Se i < $s0
	
	move $v0, $t0 #Endereço de vet para retorno
	jr $ra
	
	
	