.data
	Ent: .asciiz "Digite n: "
	Arquivo: .asciiz "gemeos.txt"
	espaco: .asciiz " "
	buffer: .space 20
.text 
main:
	li $v0, 4 # Codigo syscall escrever string
    	la $a0, Ent 
    	syscall # Escreve "Digite n: "   	
    	li $v0, 5 # Codigo syscall leitura inteiro
    	syscall # Le inteiro digitado
    	move $s0, $v0 # Armazena o valor n em s0
    	#================== ABRE ARQUIVO =====================
    	la $a0, Arquivo # a0 recebe o endereco do arquivo "gemeos.txt"
    	li $a1, 1 # Codigo syscall para ativar escrita em arquivo
    	li $v0, 13 # Codigo syscall para abertura arquivo
    	syscall
    	move $s1, $v0 # s1 armazenara o descriptor
	#===================================================
	li $t0, 1 # t0 sera o contador
loop:
	move $a0,$t0
	jal checkPrimo # Checa se o i atual é primo
	beqz $v0, iteraContador # Se for falso, retorna 0 e vai para proximo i
	addi $t1, $t0, 2 # Se nao, checa se é gemeo	
	move $a0,$t1 # t1 sera o gemeo de t0
	jal checkPrimo # Checa
	beqz $v0, iteraContador #  Se for falso, retorna 0 e vai para proximo i
escreve: # Se nao escreve
	li $v0, 0
    	move $a0, $t0 # a0 = num
    	la $a1, buffer # Endereco buffer para armazenar a sequência de caracteres
    	jal convertInt   		
    	move $a0, $s1 # Carrega descriptor
    	la $a1, buffer # a1 = i(t0) (primo que será escrito)
    	move $a2, $v0 # Numero de caracteres1
    	li $v0, 15 # Codigo escrever arquivo
   	syscall # Imprimir espaço   	
    	move $a0, $s1 # Carrega descriptor
    	li $v0, 15 # Codigo escrever arquivo
   	la $a1, espaco
 	li $a2, 1
    	syscall

iteraContador:
	addi $t0, $t0, 1 # soma no contador
	ble $t0, $s0, loop # Enquanto t0 < s0 continua o loop
saida:
	move $a0, $s1 # Carrega descriptor
    	li $v0, 16 # Codigo syscall fechar arquivo
    	syscall
	li $v0, 10
	syscall
checkPrimo:
	move $t1, $a0 # t1 é o numero atual a se checar
	li $t2, 1
	li $t4, 0 # Conta quantos divisores tem
cp:
	div $t1, $t2
	mfhi $t3 # t3 guarda o resto da divisao
	beqz $t3, divisor
	j itera
divisor:
	addi $t4, $t4, 1
itera:
	addi $t2, $t2, 1 # soma no contador
	ble $t2, $t1, cp
	beq $t4, 2, primo
	j naoPrimo
primo:
	li $v0, 1
	jr $ra
naoPrimo:
	li $v0, 0
	jr $ra
	
convertInt: # a0 = n
	div $a0, $a0, 10 # n recebe n/10
	mfhi $t3 # t3 guarda o resto da divisao
	subi $sp, $sp, 4 # Aloca espaço para 1 registrador
	sw $t3, ($sp) # Armazena o resto na pilha
	addi $v0, $v0, 1 # Soma o contador dos digitos

	bnez $a0, convertInt # Se n!= goto convertInt
	li $t2, 0 # t2 = 0
cI:
	lw $t3, ($sp) # Recupera pilha
	addi $sp, $sp, 4 # Libera pilha
	add $t3, $t3, 48 # Converte unidade para caractere
	sb $t3, ($a1) # Armazena t3 no buffer
	addi $a1, $a1, 1 # Incrementa endereco do buffer(a1)
	addi $t2, $t2, 1 # Soma contador
	bne $t2, $v0, cI # if(i != digitos) goto cI
	sb $zero, ($a1)	# Armazena zero no buffer de saida
	jr $ra
	
	
