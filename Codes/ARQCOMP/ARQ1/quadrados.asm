.data
	squares: .space 256 # Espaço para armazenar o vetor 'squares' (64 * 4 bytes)
	upTo: .word 0 # Variável para armazenar o valor de upTo
	prompt: .asciiz "n = "
	result: .asciiz "sum = "

.text
main:
	# $t0 = contador
	# $t1 = soma
	# $t2 = endereco do vetor
	# $t3 = usado para guardar vetor atual

	li $v0, 4 #Sinaliza syscall para imprimir uma string
	la $a0, prompt # carregar endereco prompt para $a0
	syscall #Printa espaco no terminal com o texto "n = "

	li $v0, 5 #Sinaliza syscall para ler input do teclado
	syscall #instrucao para ler input do teclado
	sw $v0, upTo #Aloca valor de v0 em upTo

	lw $a0, upTo # Carregar upTo como argumento para a função
	jal storeValues # chama a funcao storeValues

	lw $a0, upTo # Carregar upTo como argumento para a função
	jal computeSum # chama a funcao computeSum

	li $v0, 4 #Sinaliza syscall para imprimir uma string
	la $a0, result # carregar endereco result para $a0
	syscall #Printa espaco no terminal com o texto "sum = "

	li $v0, 1 #Sinaliza syscall para imprimir um inteiro
	la $a0, ($t1) #Carrega soma em a0
	syscall #Printa soma no terminal

	li $v0, 10 # Código de serviço para sair do programa
	syscall

storeValues:
	li $t0, 0 # int i = 0
	la $t2, squares # t2 armazena o endereco de squares

loop1:#loop referente a storeValues
	mul $t1, $t0, $t0 # Calcular o quadrado
	sw $t1, 0($t2) # Armazenar o quadrado no vetor squares

	addi $t0, $t0, 1 # Incrementar o índice
 	beq $t0, $a0, end1  # Se o índice for igual a n, sair do loop
	addi $t2, $t2, 4 # Avançar para o próximo elemento no vetor
	
	j loop1

end1: #final refetente a storeValues
	jr $ra #retorna para local em que a funcao foi chamada na main

computeSum:
	li $t0, 0 # int i = 0
	li $t1, 0 # int sum = 0
	la $t2, squares # t2 armazena o endereco de squares

loop2:#loop referente a computeSum
	lw $t3, 0($t2) # Carregar o elemento atual do vetor 'squares'
	add $t1, $t1, $t3  # Adicionar elemento a soma

	addi $t0, $t0, 1 # Incrementar o índice
	beq $t0, $a0, end2 # Se o índice for igual a n, sair do loop
	addi $t2, $t2, 4 # Avançar para o próximo elemento no vetor
	
	j loop2

end2: #final refente a computeSum
	jr $ra #retorna para local em que a funcao foi chamada na main
