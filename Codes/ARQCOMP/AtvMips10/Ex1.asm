.data
	msg1: .asciiz "Digite n: "
	msg2: .asciiz "Vetor["
	msg3: .asciiz "]: "
	msg4: .asciiz "Vetor = [ "
	msg5: .asciiz "\nVetorInvertido = [ "
	msg6: .asciiz "]"
	
.text
main:
	la $a0, msg1
	li $v0, 4
	syscall # Escreve "Digite n: "
	li $v0, 5 
	syscall # Le inteiro
	move $t0, $v0	# Armazena inteiro lido em t0
	mul $t0, $t0, 4	# Multiplica t0 por 4 tamanho do inteiro]
	move $a0, $t0 
	li $v0, 9 # Codigo de alocar memoria
	syscall # Aloca t0*4 de memoria para o vetor
	move $t1, $v0	# Armazena vetor principal em t1
	move $a0, $t0	 
	li $v0, 9 # Codigo de alocar memoria	 
	syscall # Aloca t0*4 de memoria para o vetor
	move $t2, $v0 # Armazena vetor invertido em t2
	move $a0, $t1
	jal lerVetor # funcao de ler o vetor
	move $t1, $v0
	la $a0, msg4
	li $v0, 4
	syscall # Escreve "Digite n: "
	move $a0, $t1
	jal escreve
	move $t1, $v0
	la $a0, msg6
	li $v0, 4
	syscall # Escreve "Digite n: "
	move $a0, $t2
	jal inverte
	move $t2, $v0
	add $t5, $t2, $t0
	move $a0, $t2
	la $a0, msg5
	li $v0, 4
	syscall # Escreve "Digite n: "
	move $a0, $t2
	jal escreve
	la $a0, msg6
	li $v0, 4
	syscall # Escreve "Digite n: "
	li $v0, 10	# codigo syscall finalizar programa
	syscall
lerVetor: 
	move $t9, $a0
	move $s0, $a0	# s0 armazena vetor
	li $t3, 1 # Inicia contador
	add $t5, $a0, $t0 # t5 guarda posicao final do vetor
lv:
	bge $s0, $t5, fimLv # Verifica se chegou ao fim do vetor
	la $a0, msg2 
	li $v0, 4	 
	syscall # Escreve "Vetor["
	move $a0, $t3 # a0 recebe o contador
	li $v0, 1  
	syscall # Escreve posicao atual do vetor
	la $a0, msg3 
	li $v0, 4  
	syscall # Escreve "]: "
	li $v0, 5 
	syscall # Le inteiro		
	sw $v0, ($s0)	# Aloca valor lido no vetor	
	#ITERACOES
	addi $s0, $s0, 4 
	addi $t3, $t3, 1 
	j lv
fimLv:
	move $v0, $t9
	jr $ra 
escreve:
	move $t9, $a0
	move $s0, $a0 # s0 recebe vetor
	add $t5, $a0, $t0 # t5 guarda posicao final do vetor
e:
	bge $s0, $t5, fimEv # Verifica se chegou ao fim do vetor
	lw $a0, ($s0) # Carrega elemento do vetor
	li $v0, 1
	syscall	# Escreve elemento atual	
	li $a0, 32 
	li $v0, 11
	syscall # Escreve espaco
	# ITERA
	addi $s0, $s0, 4
	j e
fimEv:
	move $v0, $t9
	jr $ra
inverte:
	move $t9, $a0
	move $s0, $t5	#s0 = endereço final do vetA
	subi $s0, $s0, 4	#volta uma posicao do vetA
	move $s1, $t2	#s1 = endereco inicial do vetB
i:
	blt $s0, $t1, fim_inverter
	lw $s3, ($s0)	# armazena o valor final do vetor principal no invertido
	sw $s3, ($s1)
	subi $s0, $s0, 4	
	addi $s1, $s1, 4	 
	j i

fim_inverter:
	move $v0, $t9
	jr $ra	 
	
