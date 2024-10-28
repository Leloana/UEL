.data
	ent: .asciiz "Insira o valor de Vet["
	ent2: .asciiz "]: "
	.align 2
	vet: .space 48
	counter: .word 12
	newline: .asciiz "\n"
	ktext: .asciiz "\nDigite K:"
	kmenortext: .asciiz "\nMenores que 2*k:"
	kmaiortext: .asciiz "Maiores que k:"
	k: .word 0 # Variável para armazenar o valor de k
	kDois: .word 0 # Variável para armazenar o valor do segundo k
	somaPares:.asciiz "Soma dos pares:"
	kDoistext: .asciiz "\nDigite o segundo k:"
	iguaisak: .asciiz "Iguais a k:"
	perfect: .asciiz "\nSoma dos Perfeitos:"
	semi: .asciiz "\nSoma Semiprimos: "
	subtracao: .asciiz "\nPerfeitos - Semiprimos = "
	msgerro: .asciiz "\nValor invalido de k"
	entrek: .asciiz "\nEntre k e 2 * k: "
	
.text

main:  	
	lw $t3, counter #Tamanho do vetor para usar em blt
	la $v0, vet #Armazena endereço do vetor
	move $a0, $v0
	jal leitura #Funcao de leitura
	move $a0, $v0
	jal ordena #Funcao de ordenacao em ordem crescente
	move $a0, $v0
	jal escrita #Funcao de escrita do vetor
	move $a0, $v0
	jal perfeito #Funcao que faz a conta SomaPerfeitos - SomaSemiprimos
	move $a0, $v0
	jal somapar #Funcao que faz a soma dos numeros pares
	move $a0, $v0
	jal kteste #Funcao que acha os valores maiores que a chave k 
					# e menores que 2*k no vetor
	move $a0, $v0
	jal igualk #Funcao que acha os valores iguais a chave k no vetor
finaliza:
	li $v0, 10
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
	blt $t2, $t3, loop  #Se i < $t3 (no caso $t3 = 3) continua loop
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
	blt $t2, $t3, e #Se i < $t3 (no caso $t3 = 3) continua loop
	move $v0, $t0 #Endereço de vet para retorno
	jr $ra
	
ordena:
    	move $t0, $a0 # Armazena o endereço do vetor em $t0
    	move $t1, $t0 # Armazena o endereço do vetor em $t1
    	li $t2, 0 # Inicia contador "i = 0"
o:
    	lw $t5, 0($t1) # Atual elemento do vetor
    	lw $t6, 4($t1) # Próximo elemento do vetor
	
    	blt $t6, $t5, troca
    	j oadd
troca:
    	sw $t6, 0($t1) #Coloca elemento maior no proximo endereço
    	sw $t5, 4($t1) #Coloca endereco menor no endereço anterior
	
    	la $t1, vet # reseta enderço do vetor
    	li $t2, 0
    	j o #Reseta vetor para achar proxima troca
oadd:
    	addi $t1, $t1, 4 # Vai para próximo endereço do vetor (4 pois é o tamanho de um inteiro)
    	addi $t2, $t2, 1 # Adiciona 1 no contador "i ++"
    	
    	li $t3, 11 #diminuir 1 do maximo para que nunca analise o proximo do ultimo
    	blt $t2, $t3, o # Se i < $t3 (no caso $t3 = 12) continua loop
    	lw $t3, counter #volta o tamanho do vetor para 12
    	
    	move $v0, $t0 # Endereço de vet para retorno
    	jr $ra
  
somapar:
	move $t0, $a0 # Armazena o endereço do vetor em $t0
    	move $t1, $t0 # Armazena o endereço do vetor em $t1
    	li $t2, 0 # Inicia contador "i = 0"
    	li $t5, 0 # Soma dos pares
sp:
    	lw $t6, 0($t1)    # Carrega o elemento do vetor
    	andi $t4, $t6, 1   # Verifica se é par (resto da divisão por 2)

    	bnez $t4, not_par   # Se não for par, pula para not_par
   	 # Ação a ser realizada para elementos pares
    	add $t5, $t5, $t6
not_par:	
   	addi $t1, $t1, 4   # Avança para o próximo elemento do vetor
    	addi $t2, $t2, 1   # Incrementa o índice i
    	blt $t2, $t3, sp  # Se i < tamanho, continua o loop
    
    	li $v0, 4 # Código da syscall para imprimir String
    	la $a0, newline
    	syscall
    	#=========== Soma dos pares  =====================
    	la $a0, somaPares #Carrega String "\nSoma dos pares:"
	li $v0, 4
	syscall #Escreve String
    	li $v0, 1 #Sinaliza syscall para imprimir um inteiro 				
	move $a0, $t5 #Passa o valor de t3 para a0			
	syscall #Printa valor de t2 que é a soma pares
    	
	move $v0, $t0 # Endereço de vet para retorno
    	jr $ra
    	
kteste:
	move $t0, $a0 # Armazena o endereço do vetor em $t0
    	move $t1, $t0 # Armazena o endereço do vetor em $t1
    	li $t2, 0 # Inicia contador "i = 0"
    	li $t6, 0 #inicia contador de maiores que k
    	li $t8, 0 #inicia contador de menores que 2 * k
	li $s5, 0 #inicia contador de menores que k

	la $a0, ktext #Carrega String "Digite K:
	li $v0, 4
	syscall #Escreve String
	li $v0, 5   # Código da syscall para ler inteiro
    	syscall  # Leitura do input do teclado (inteiro)
    	
    	bltz $v0, erro
    	
    	sw $v0, k  # Armazena o valor lido no endereço alocado
    	lw $t5, k
kt:
	lw $t4, 0($t1)    # Carrega o elemento do vetor
	beq $t4, $t5 kkmaior
	blt $t4, $t5, kmenor # Checa se valor atual do vetor é maior que k
	addi $t6,$t6, 1 #adiciona um no contador
kmenor:
	bgt $t4, $t5, pula
	addi $s5,$s5,1 #adiciona 1 menor que k
pula:
	li $t7, 0
	add $t7, $t5, $t5 # $t7 recebe 2*k
	blt $t7,$t4, kkmaior
	addi $t8,$t8, 1
kkmaior:
	addi $t1, $t1, 4   # Avança para o próximo elemento do vetor
    	addi $t2, $t2, 1   # Incrementa o índice i
    	blt $t2, $t3, kt  # Se i < tamanho, continua o loop
    	
    	#=========== Valores maiores que k =====================
    	la $a0, kmaiortext #Carrega String "\Maiores que k::
	li $v0, 4
	syscall #Escreve String
    	li $v0, 1 #Sinaliza syscall para imprimir um inteiro 				
	move $a0, $t6 #Passa o valor de t6 para a0			
	syscall 
    	#=========== Valores menores que 2 * k =====================	
	la $a0, kmenortext #Carrega String "\Menores que 2*k::
	li $v0, 4
	syscall #Escreve String
    	li $v0, 1 #Sinaliza syscall para imprimir um inteiro 				
	move $a0, $t8 #Passa o valor de t8 para a0			
	syscall 
	
	#=========== Valores menores que 2 * k =====================	
	la $a0, entrek #Carrega String "\Menores que 2*k::
	li $v0, 4
	syscall #Escreve String
    	li $v0, 1 #Sinaliza syscall para imprimir um inteiro 				
	move $a0, $s5 #Passa o valor de t8 para a0			
	syscall 
    	
	move $v0, $t0 # Endereço de vet para retorno
    	jr $ra
igualk:
	move $t0, $a0 # Armazena o endereço do vetor em $t0
    	move $t1, $t0 # Armazena o endereço do vetor em $t1
    	li $t2, 0 # Inicia contador "i = 0"
    	li $t6, 0 #inicia contador de iguais a k

	la $a0, kDoistext #Carrega String "\nDigite o segundo K:"
	li $v0, 4
	syscall #Escreve String
	li $v0, 5   # Código da syscall para ler inteiro
    	syscall  # Leitura do input do teclado (inteiro)
    	sw $v0, kDois  # Armazena o valor lido no endereço alocado
    	lw $t5, kDois
kdois:
	lw $t4, 0($t1)    # Carrega o elemento do vetor
	bne $t4, $t5, diffk # Checa se valor atual do vetor é igual a k
	addi $t6,$t6, 1 #adiciona um no contador

diffk:
	addi $t1, $t1, 4   # Avança para o próximo elemento do vetor
    	addi $t2, $t2, 1   # Incrementa o índice i
    	blt $t2, $t3, kdois  # Se i < tamanho, continua o loop
	
	#=========== Valores iguais a k =====================	
	la $a0, iguaisak #Carrega String "\n Iguais a k:"
	li $v0, 4
	syscall #Escreve String
    	li $v0, 1 #Sinaliza syscall para imprimir um inteiro 				
	move $a0, $t6 #Passa o valor de t6 para a0			
	syscall 
	
	move $v0, $t0 # Endereço de vet para retorno
    	jr $ra
    	
perfeito:
	move $t0, $a0 # Armazena o endereço do vetor em $t0
    	move $t1, $t0 # Armazena o endereço do vetor em $t1
    	li $t2, 0 # Inicia contador "i = 0"
    	li $t8, 0 # Inicia a soma dos perfeitos do vetor
p:
	lw $t4, 0($t1)    # Carrega o elemento do vetor
	li $t5, 1 # Inicia divisor "i = 1"
	li $t7, 0 # Inicia a soma do perfeito
pfto:
	divu $t4, $t5 # Divide $t4 (dividendo) por $t5(divisor)
        mfhi $t6 # Move o resto para $t6

	bnez $t6, addContador # se t6 = 0 entao ele é divisor do numero
	add $t7,  $t7, $t5 #soma o divisor do numero em soma
addContador:
	addi $t5, $t5, 1 # Adiciona 1 no divisor
	blt $t5, $t4, pfto # Se o divisor ainda não dividiu ate o dividendo continua
	bne $t7, $t4, continue
	add $t8, $t8, $t7 # A soma dos perfeitos do vetor 
continue: 
	addi $t1, $t1, 4   # Avança para o próximo elemento do vetor
	addi $t2, $t2, 1 #Soma 1 no contador
	blt $t2, $t3, p  # Se i < numero, continua o loop
	
	#=========== Soma dos Perfeitos =====================	
	la $a0, perfect #Carrega String "Soma dos Perfeitos:"
	li $v0, 4
	syscall #Escreve String
    	li $v0, 1 #Sinaliza syscall para imprimir um inteiro 				
	move $a0, $t8 #Passa o valor de t8 para a0			
	syscall 
	
semiprimo:
    	move $t1, $t0 # Armazena o endereço do vetor em $t1
    	li $s2, 0 # Inicia contador "i = 0"
    	li $t7, 0 # Inicia a soma dos semiprimos do vetor
    	li $t6, 2 # Sera usado para dividir o numero por 2
sep:
	li $s3, 0 #carrega a quantidade de fatores
	li $t2, 1 # Inicia os divisores "i = 1"
	lw $t4, 0($t1)    # Carrega o elemento do vetor
	ble $t4, $t6, contiPrimo # Se o vetor atual for menor que dois vai para proximo passo
	div $t4, $t6 # vetor dividido por 2
	mflo $t5 # armazena em t5 a divisao
	
for:
	addi $t2, $t2, 1  # incrementa o contador  	
	bgt $t2, $t5, fim # Se o contador superar a metade do vetor atual, encerra busca
	
while:
	div $t4, $t2 #se o resto for igual a 0 é divisor
	mfhi $s1 #resto
			
	bne $s1, $zero, for # Se resto for diferente nao é divisor, vai para proximo possivel divisor
	
	div $t4, $t2 # Fatora t4 
	mflo $t4 #O resto da divisao vai ser dividido posteriormente
	addi $s3, $s3, 1 #armazena numero de fatores
			
	j while	
fim:
	bne $s3, $t6, contiPrimo # Se o numero tiver 2 fatores ele é semiprimo
	lw $t4, 0($t1) #Carrega o valor inicial do numeor para somá-lo
	add $t7, $t7, $t4
contiPrimo:	
	addi $t1, $t1, 4  # Avança para o próximo elemento do vetor
	addi $s2, $s2, 1 #Soma 1 no contador
	blt $s2, $t3, sep # Se i < numero, continua o loop

	#=========== Soma dos Semiprimos =====================	
	li $v0, 4 # codigo SysCall para escrever strings
    	la $a0, semi #Carrega String "Soma Semiprimos:"
    	syscall#Escreve String
    	
    	move $a0, $t7	#  # Carrega o valor da soma
	li $v0, 1 #Sinaliza syscall para imprimir um inteiro 
	syscall		
	
	#=========== Perfeitos - Semiprimos =====================	
	li $v0, 4	# codigo SysCall para escrever strings
    	la $a0, subtracao #Carrega String "Perfeitos - Semiprimos = "
    	syscall#Escreve String
    	
    	sub $t8,$t8,$t7
    	
    	move $a0, $t8 # Carrega o valor da subtracao
	li $v0, 1 #Sinaliza syscall para imprimir um inteiro 
	syscall	
	
	move $v0, $t0
	jr $ra

erro:
	li $v0, 4	# codigo SysCall para escrever strings
    	la $a0, msgerro #Carrega String "Perfeitos - Semiprimos = "
    	syscall#Escreve String
	j finaliza
