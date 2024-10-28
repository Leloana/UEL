.data
	espaco: .asciiz " "
	textA: .asciiz "A: "
	textB: .asciiz "B: "
	multiplos: .asciiz "Multiplos em (A : AxB):"

.text
main:
	# $t0 = A
	# $t1 = B
	# $t02 = A * B
	# $t03 = contador
	# $t04 = multiplo atual
	
	li $v0, 4  #Sinaliza syscall para imprimir uma string
	la $a0, textA #Carrega o endereco de textA em a0
	syscall #Printa textA no terminal com o texto "A: "
	
	#leitura de input
	li $v0, 5 #Sinaliza syscall para ler input do teclado
	syscall #instrucao para ler input do teclado
	move $t0, $v0 #Aloca valor de A em t0
	blez $t0, exit #Se A for invalido acaba programa

	li $v0, 4 #Sinaliza syscall para imprimir uma string
	la $a0, textB #Carrega o endereco de textB em a0
	syscall #Printa textA no terminal com o texto "B: "
	
	#leitura de input	
	li $v0, 5 #Sinaliza syscall para ler input do teclado
	syscall #instrucao para ler input do teclado
	move $t1, $v0 #Aloca valor de B em t1
	blez $t1, exit #Se B for invalido acaba programa
	
    	mul $t2, $t0, $t1 #$t3 = A * B
	li $t3, 1 #Load 1 para $t2

	li $v0, 4 #Sinaliza syscall para imprimir uma string
	la $a0, multiplos #carregar endereco multiplos para $a0
	syscall  #Printa textA no terminal com o texto "Multiplos em (A : AxB): "
    
checaMultiplo: #loop que checa os multiplos de A no intevalo (A : AxB)
	mul $t4, $t0, $t3 #Multiplica A x contador e armazena em t4 
	bgt $t4, $t2, exit #Jump para exit se multiplo de A for maior que AxB

	li $v0, 4 #Sinaliza syscall para imprimir uma string
	la $a0, espaco # carregar endereco espaco para $a0
	syscall #Printa espaco no terminal com o texto " "
	
	li $v0, 1 #Sinaliza syscall para imprimir um inteiro
	move $a0, $t4 #Carrega multiplo de A em $a0
	syscall  #Printa multiplo no terminal

	addi $t3, $t3, 1 #incrementa contador
	j checaMultiplo #Jump para checaMultiplo
exit: