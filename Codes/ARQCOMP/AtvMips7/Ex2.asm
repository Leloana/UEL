.data
	Ent1: .asciiz "Insira um CPF no formato xxxxxxxxx-xx: "
	Invalido: .asciiz "CPF INVALIDO"
	Valido: .asciiz "CPF VALIDO"
.text
main:
	li $v0, 4 # Escreve "Insira um CPF no formato xxxxxxxxx-xx: "
	la $a0, Ent1
	syscall
	
	li $v0, 9 # Codigo para alocar memoria
	la $a0, 64 # Limite de caracteres do cpf
	syscall # Aloca a memoria
	move $a1, $v0 # Guarda a string em a0
	
	li $v0, 8 # Codigo para ler string
	move $a0, $a1
	syscall 
	move $a1, $a0 # Guarda a string no a1
	jal checkCPF
	move $a2, $v0 # Endereco do vetor fica em a2
	jal checkVector # Retorna 0 caso o CPF seja INVALIDO e 1 caso seja VALIDO
	beqz $v0, false
#==============	SAIDA ==========================
true:# Escreve que o CPF é Valido
	li $v0, 4
  	la $a0, Valido
  	syscall
  	j saida
false:# Escreve que o CPF é Invalido
  	li $v0, 4
  	la $a0, Invalido
  	syscall
#==============================================

saida:
	li $v0, 10
	syscall

checkCPF:
	move $t0, $a1 # Guarda o endereco da string em t0
	li $t1, 0 # Contador
	#============== ALOCA VETOR PARA O CASO DA STRING SER VALIDA ====================
	li $a0, 11	# n
	sll $a0, $a0, 2	# aux = n * 4
	li $v0, 9	# C�digo de aloca��o de mem�ria
	syscall		# Aloca mem�ria
	move $t4, $v0 # Guarda o endereco do vetor em t4
	move $t5, $t4
	#================================================================================
c:
	lb $t3, ($t0) # Armazena o caracter em t3
	beq $t3, 10, size	# if ($t3 == "\0") goto comparaTamanho
	beq $t3, 45, hyfen	# if ($t3 == "-") goto isHyfen
	blt $t3, 48, invalid	# if ($t3 < 48) goto notNumber
	bgt $t3, 57, invalid	# if ($t3 > 57) goto notNumber 
	subi $t3, $t3, 48# Converte char para int
	sw $t3, ($t5) # Vetor[i] = $t3
	add $t5, $t5, 4	# Vetor[++i]
itera:
	add $t0, $t0, 1	# Vai para proximo elemento da string CPF
	addi $t1, $t1, 1 # Contador de tamanho aumenta 1
	j c # COntinua loop
hyfen:
	bne $t1, 9, invalid # Caso a posicao do hifen seja diferente de 9
	j itera
invalid:
	li $v0, 4
	la $a0, Invalido
	syscall
	li $v0, 10
	syscall # Sai do codigo
size:
	bne $t1, 12, invalid # Se o tamanho da string for diferente de 12 (11 numeros + hifen)
	move $v0, $t4 # Retorna vetor
	jr $ra	
checkVector:
	li $t3, 10# Multiplicador do primeiro digito verificador 
	li $t6, 9 # Flag para o primeiro digito verificador 
	move $t0, $a2 # Salva endere�o base de Vetor
	move $t1, $t0 # Iterador
	add $t1, $t1, 36 # Penultimo digito
	move $t4, $t1 # Posicao do primeiro digito verificador 
restart:
	move $t1, $t0 # t1 recebe endereco do vetor
	li $t2, 0 # Contador
	li $t8, 0 # Soma = 0
cV:
	lw $t9, ($t1) # t9 recebe o vetor i
	mul $t9, $t9, $t3 # Multiplica o vetor por 10-9-8-7-...-2
	add $t8, $t8, $t9 # soma += valor
	subi $t3, $t3, 1 # Diminui o multiplicador pois deve ser decrescente
	#Itera
	addi $t2, $t2, 1 # Soma no contadors
	add $t1, $t1, 4	 # Passa para proximo elemento do vetor
	blt $t2, $t6, cV # Se t2 < 9 continua 
	#Fim do loop
	div $t8, $t8, 11 # soma / 11
	mfhi $t5 # Resto
	blt $t5, 2, menorQueDois # if (resto < 2) goto menorQueDois	
maiorQueDois:
	subi $t5, $t5, 11# Subtrai-se o valor obtido de 11
	mul $t5, $t5, -1# -resto (Inveter a subtracao, pois eu fiz [resto - 11] e nao [11 - resto])
	lw $t9, ($t4)# t9 recebe o digito verificador 
	bne $t5, $t9, cpfInvalido # Se ot5 for diferente de t9 o CPF é INVALIDO
	beq $t2, 10, cpfValido  # Se t5 for o ultimo valor o CPF é valido
	j segundoVerificador	# goto resetaValores
menorQueDois:
	lw $t9, ($t4) # t9 recebe o digito verificador 
	bnez $t9, cpfInvalido # Se o elemento for diferente de zero o CPF é INVALIDO
	beq $t2, 10, cpfValido # Se 0 for o ultimo valor o CPF é valido
	#Se nao continua, porem analisa o segundo digito verificador
segundoVerificador:
	li $t3, 11# Multiplicador do segundo digito verificador 
	li $t6, 10 # Flag para o segundo digito verificador
	add $t4, $t4, 4	# Passa para segundo digito verificador
	j restart	
cpfInvalido:
	li $v0, 0 # Retorna false
	jr $ra	
cpfValido:
	li $v0, 1 # Retorna true
	jr $ra
	
	
	
	