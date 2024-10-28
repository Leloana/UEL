.data
	vetor: .word -2, 4, 7, -3, 0, -3, 5, 6
	somaN: .word 0
	somaP: .word 0
	saidaP: .asciiz "A soma dos valores positivos = "
	saidaN: .asciiz "\nA soma dos valores negativos = "
	tamanhoVetor: .word 8

.text
	la $t0, vetor #Carrega endereço do vetor	
	lw $t1, tamanhoVetor #Load no tamanho do vetor que é 8
	lw $t2, somaP #Load na soma dos positivos que é 0
	lw $t3, somaN #Load na soma dos negativos que é 0
	# $t04 = vetor
	
loop:#loop que passa pelo vetor para fazer soma dos negativos e positivos
	lw $t4, 0($t0) #Elemento do vetor fica em t4
	bgez $t4, soma_Positivo #Caso o valor atual do vetor for maior que 0, soma para soma_Positivo
	add $t3, $t3, $t4 #Caso seja negativo soma o vetor atual aos negativos
	j contador #Pula para proximo valor do vetor

soma_Positivo:#caso seja um numero maior que 0 vem para esse campo
	add $t2, $t2, $t4 #incrementa soma do positivo

contador:#adiciona um ao contador até que o vetor seja completamete percorrido
	addi $t0, $t0, 4 #inteiro ocupa 4 bits   
	addi $t1, $t1, -1 #decrementa o contador
	bnez $t1, loop #se contador zerar acaba o loop

	li $v0, 4 #Sinaliza syscall para imprimir uma string		
	la $a0, saidaP #Carrega o endereco de saidaP em a0
	syscall #Printa saidaP no terminal com o texto "A soma dos valores positivos = "
	li $v0, 1 #Sinaliza syscall para imprimir um inteiro 			
	move $a0, $t2 #Passa o valor de t2 para a0
	syscall #Printa valor de t2 que é a soma dos positivos

	li $v0, 4 #Sinaliza syscall para imprimir uma string					
	la $a0, saidaN #Carrega o endereco de saidaN em a0		
	syscall #Printa saidaP no terminal com o texto "\nA soma dos valores negativos = "
	li $v0, 1 #Sinaliza syscall para imprimir um inteiro 				
	move $a0, $t3 #Passa o valor de t3 para a0			
	syscall #Printa valor de t2 que é a soma dos negativos
