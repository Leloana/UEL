.data
	Arquivo: .asciiz "dados1.txt"
	buffer: .space 1024
	maiorText: .asciiz "Maior valor do vetor: "
	menorText: .asciiz "\nMenor valor do vetor: "
	oddText: .asciiz "\nNumero de elementos impares do vetor: "
	evenText: .asciiz "\nNumero de elementos pares do vetor: "
	somaText: .asciiz "\nSoma dos elementos do vetor: "
	crescenteText: .asciiz "\nO vetor em ordem crescente: "
	decrescenteText: .asciiz "\nO vetor em ordem decrescente: "
	produtoText: .asciiz "\nProduto dos elementos do vetor: "
	numText: .asciiz "\nNumero de caracteres (contando espacos)do vetor: "
	ErrorArq: .asciiz "Erro ao abrir o arquivo"
	ErrorVetor: .asciiz "Vetor invalido"
.text
main:
	la $a0, Arquivo
	li $v0, 13
	li $a1, 0 #Abre arquivo apenas para leitura
	li $a2, 0 
	syscall	# Abre o arquivo
	blt $v0, 0, erroAbreArquivo #Checa se o arquivo foi aberto corretamente
	move $t0, $v0# Salva o identificador do arquivo
	alocaVetor:
	li $t1, 0# controle = 0
	li $t3, 0# contador = 0
lAloca:
	move $a0, $t0 # Identificadpr dp arquivo vai para a0
	la $a1, buffer  
	li $a2, 1 
	li $v0, 14 
	syscall # Le o arquivo 
	beq $v0, $zero, proxNum # Se o numero atual for NULO vai para final
	lb $t2, ($a1) # t2 guarda numero
	beq $t2, 32, proxNum # Se for um espaco acaba
	blt $t2, 48, naoNum # Se for menor que zero acaba
	bgt $t2, 57, naoNum # Se for maior que nove acaba
	li $t1, 1 # Contador
	j lAloca 	
proxNum:
	beq $v0, $zero, fimLeitura	# Se o numero atual for NULO vai para final
	beq $t1, 0, lAloca
	li $t1, 0 # Zera contador
	addi $t3, $t3, 1  # Itera
	j lAloca		 		
fimLeitura:
	addi $t3, $t3, 1 # Itera
	mul $t3, $t3, 4 # Itera do tamanho de um inteiro
	move $a0, $t3 # Carrega tamanho do vetor
	li $v0, 9  
	syscall # Aloca Vetor
	div $t3, $t3, 4 # contador
	move $s0, $v0 # Vetor vai para s0
	move $a0, $t0  
	li $v0, 16   
	syscall # fecha arquivo 
	jal transformArq# Le o arquivo e aloca os dados em um vetor de inteiros
	jal maior# Passa pelo vetor e acha o maior valor
	jal menor# Passa pelo vetor e acha o menor valor
	jal impares# Passa pelo vetor e acha a quantidade de numeros impares nele
	jal pares# Passa pelo vetor e acha a quantidade de numeros pares nele
	jal soma# Soma os valores do vetor
	jal crescente# Organiza o vetor em ordem crescente
	jal decrescente# Organiza o vetor em ordem decrescente
	jal produto# Faz o produto dos valores do vetor
	jal quantidadeCaracteres# Calcula a quantidade de caracteres do vetor
	j fim # goto encerraPrograma	
naoNum:
	la $a0, ErrorVetor 
	li $v0, 4  
	syscall # Escreve string "Vetor invalido"
	j fim# goto encerraPrograma

erroAbreArquivo:
	la $a0, ErrorArq 
	li $v0, 4 
	syscall # Escreve string "Erro ao abrir o arquivo"
	j fim# goto encerraPrograma	
fim:
	li $v0, 10
	syscall	# Encerra o programa	
transformArq:
	la $a0, Arquivo
	li $v0, 13 
	li $a1, 0  
	li $a2, 0  
	syscall # Abre o arquivo para leitura
	blt $v0, 0, erroAbreArquivo	# Identifica se houve erro no processo
	move $t0, $v0 # Salva arquivo em t0	
	li $t1, 0 
	li $t4, 0 
	li $t5, 0 
	move $s1, $s0 # s1 recebe o endereco do vetor	
lArqVec:
	move $a0, $t0  
	la $a1, buffer  
	li $a2, 1  
	li $v0, 14  
	syscall # Abre o arquivo para leitura
	beq $v0, $zero, espaco # Se o atual for nulo vai para condicao
	lb $t2, ($a1) # Carrega caracter	
charToInt:
	beq $t2, 32, espaco	# Se o atual for um espaco vai para condicao
	blt $t2, 48, naoNum	# Se for menor que 0 vai para condicao
	bgt $t2, 57, naoNum	# Se for maior que 9 vai para condicao
	li $t1, 1		# controle = 1
	#================ CONVERTENDO CHAR PARA INT ========================
	subi $t2, $t2, 48 
	mul $t5, $t5, 10 
	add $t5, $t5, $t2 
	j lArqVec 	
espaco:
	beqz $t1, lArqVec  
	li $t1, 0 # Zera t1s
	sw $t5, ($s1) # t5 eh o valor atual do vetor
	li $t5, 0 # acumulador = 0
	# ITERACOES
	add $s1, $s1, 4 # Vai par aproximo elemento do vetor
	addi $t4, $t4, 1 # i++
	blt $t4, $t3, lArqVec 
	move $a0, $t0  
	li $v0, 16  
	syscall # fecha arquivo
	jr $ra  			
maior:
	move $s1, $s0 # Endereco do vetor vai para s1
	lw $t1, ($s1) # maior = vetor[0]
	li $t2, 0# contador	
lMValor:
	lw $t4, ($s1) # aux = vetor[i]
	bgt $t4, $t1, ehMaior # if (aux > maior) goto ehMaior
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lMValor # if (i < n) goto loopMaiorValor
	j fimMaiorValor # goto fimMaiorValor	
ehMaior:
	move $t1, $t4 # maior = aux
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lMValor # if (i < n) goto loopMaiorValor
	j fimMaiorValor # goto fimMaiorValor		
fimMaiorValor:
	la $a0, maiorText# Carrega endere�o da string
	li $v0, 4# Codigo para escrever string
	syscall	# Escreve string
	move $a0, $t1# Carrega o maior valor
	li $v0, 1# Codigo para escrever inteiros
	syscall	# Escreve inteiro
	jr $ra	# Retorno para a main		
menor:
	move $s1, $s0	# Salve endere�o do vetor
	lw $t1, ($s1)	# menor = vetor[0]
	li $t2, 0	# i
lMeValor:
	lw $t4, ($s1) # aux = vetor[i]
	blt $t4, $t1, ehMenor # if (aux > maior) goto ehMaior
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3,lMeValor  	# if (i < n) goto loopMaiorValor
	j fimMenorValor # goto fimMenorValor	
ehMenor:
	move $t1, $t4 # menor = aux
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lMeValor	# if (i < n) goto loopMaiorValor
	j fimMenorValor # goto fimMenorValor	
fimMenorValor:
	la $a0, menorText	# Carrega endere�o da string
	li $v0, 4	# Codigo para escrever string
	syscall		# Escreve string
	move $a0, $t1	# Carrega o maior valor
	li $v0, 1	# C�digo para escrever inteiros
	syscall		# Escreve inteiro
	jr $ra		# Retorno para a main
impares:
	move $s1, $s0	# Salva endere�o do vetor
	li $t1, 0	# contador
	li $t2, 0	# i
lImpar:
	lw $t4, ($s1) # aux = vetor[i]
	div $t4, $t4, 2 # aux = aux/2
	mfhi $t4 # resto
	bnez $t4, ehImpar # if (resto != 0) goto ehImpar
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lImpar	# if (i < n) goto loopQuantidadeImpar
	j fimQuantidadeImpar # goto fimQuantidadeImpar
ehImpar:
	addi $t1, $t1, 1 # contador++
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lImpar	# if (i < n) goto loopQuantidadeImpar
	j fimQuantidadeImpar # goto fimQuantidadeImpar
fimQuantidadeImpar:
	la $a0, oddText	# Carrega endere�o da string
	li $v0, 4	# C�digo para escrever string
	syscall		# Escreve string
	move $a0, $t1	# Carrega o maior valor
	li $v0, 1	# C�digo para escrever inteiros
	syscall		# Escreve inteiro
	jr $ra		# Retorno para a main	
pares:
	move $s1, $s0	# Salva endere�o do vetor
	li $t1, 0	# contador
	li $t2, 0	# i
lPar:
	lw $t4, ($s1) # aux = vetor[i]
	div $t4, $t4, 2 # aux = aux/2
	mfhi $t4 # resto
	beqz $t4, ehPar # if (resto != 0) goto ehPar
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lPar# if (i < n) goto loopQuantidadeImpar
	j fimQuantidadePar# goto fimQuantidadePar
ehPar:
	addi $t1, $t1, 1 # contador++
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lPar# if (i < n) goto loopQuantidadePar
	j fimQuantidadePar# goto fimQuantidadePar
fimQuantidadePar:
	la $a0, evenText	# Carrega endere�o da string
	li $v0, 4	# C�digo para escrever string
	syscall		# Escreve string
	move $a0, $t1	# Carrega o maior valor
	li $v0, 1	# C�digo para escrever inteiros
	syscall		# Escreve inteiro
	jr $ra		# Retorno para a main	
soma:
	move $s1, $s0	# Salva endere�o do vetor
	li $t1, 0	# soma
	li $t2, 0	# i		
lSoma:
	lw $t4, ($s1) # aux = vetor[i]
	add $t1, $t1, $t4 # soma += aux
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lSoma	# if (i < n) goto loopSomaValores
	j fimSomaValores # goto fimSomaValores	
fimSomaValores:
	la $a0, somaText	# Carrega endere�o da string
	li $v0, 4	# Codigo para escrever string
	syscall		# Escreve string
	move $a0, $t1	# Carrega o maior valor
	li $v0, 1	# Codigo para escrever inteiros
	syscall # Escreve inteiro
	jr $ra # Retorno para a main
crescente:
	move $s1, $s0	# Salva o endere�o do vetor
	move $s2, $s0	# Salva o endere�o do vetor
	li $t1, 0	# j = 0
	li $t2, 0	# i = 0	
lUmCres:
	lw $t4, ($s1)	# aux = vetor[i]
		
lDoisCres:
	lw $t5, ($s2) # aux2 = vetor[j]
	bgt $t5, $t4, trocaMaior # if (aux2 > aux) goto trocaMaior
	add $s2, $s2, 4 # vetor[j++]
	addi $t1, $t1, 1 # j++
	blt $t1, $t3, lDoisCres	# if (j < n) goto loopInternoOrdemCrescente
	move $s2, $s0 # Reseta o ponteiro
	li $t1, 0 # j = 0
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lUmCres	# if (i < n) goto loopExternoOrdemCrescente
	li $t2, 0 # i = 0
	move $s1, $s0 # Reseta ponteiro
	j fimOrdemCrescente # goto fimOrdemCrescente		
trocaMaior:
	sw $t5, ($s1) # vetor[i] = aux2
	sw $t4, ($s2) # vetor[j] = aux
	move $t4, $t5 # aux = aux2
	add $s2, $s2, 4 # vetor[j++]
	addi $t1, $t1, 1 # j++
	blt $t1, $t3, lDoisCres	# if (j < n) goto loopInternoOrdemCrescente
	move $s2, $s0 # Reseta o ponteiro
	li $t1, 0 # j = 0
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lUmCres	# if (i < n) goto loopExternoOrdemCrescente
	li $t2, 0 # i = 0
	move $s1, $s0 # Reseta ponteiro
	j fimOrdemCrescente # goto fimOrdemCrescente		
fimOrdemCrescente:
	la $a0, crescenteText	# Carrega endere�o da string
	li $v0, 4	# Codigo para escrever string
	syscall		# Escreve string		
lFimCres:
	lw $a0, ($s1) # Carrega vetor[i]
	li $v0, 1 # Codigo para escrever inteiros
	syscall # Escreve inteiro
	li $a0, 32 # Carrega " "
	li $v0, 11 # Codigo para escrever caracter
	syscall # Escreve caracter
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lFimCres	# if (i < n) goto loopFimOrdemCrescente
	jr $ra # retorno para a main				
decrescente:
	move $s1, $s0	# Salva o endereco do vetor
	move $s2, $s0	# Salva o endereco do vetor
	li $t1, 0	# j = 0
	li $t2, 0	# i = 0	
lUmDecres:
	lw $t4, ($s1)	# aux = vetor[i]		
lDoisDecres:
	lw $t5, ($s2) # aux2 = vetor[j]
	blt $t5, $t4, trocaMenor # if (aux2 > aux) goto trocaMenor
	add $s2, $s2, 4 # vetor[j++]
	addi $t1, $t1, 1 # j++
	blt $t1, $t3, lDoisDecres	# if (j < n) goto loopInternoOrdemDecrescente
	move $s2, $s0 # Reseta o ponteiro
	li $t1, 0 # j = 0
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lUmDecres	# if (i < n) goto loopExternoOrdemDecrescente
	li $t2, 0 # i = 0
	move $s1, $s0 # Reseta ponteiro
	j fimOrdemDecrescente				# goto fimOrdemDecrescente		
trocaMenor:
	sw $t5, ($s1) # vetor[i] = aux2
	sw $t4, ($s2) # vetor[j] = aux
	move $t4, $t5 # aux = aux2
	add $s2, $s2, 4 # vetor[j++]
	addi $t1, $t1, 1 # j++
	blt $t1, $t3, lDoisDecres	# if (j < n) goto loopInternoOrdemDecrescente
	move $s2, $s0 # Reseta o ponteiro
	li $t1, 0 # j = 0
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lUmDecres	# if (i < n) goto loopExternoOrdemDecrescente
	li $t2, 0 # i = 0
	move $s1, $s0 # Reseta ponteiro
	j fimOrdemDecrescente # goto fimOrdemDecrescente			
fimOrdemDecrescente:
	la $a0, decrescenteText	# Carrega endere�o da string
	li $v0, 4	# C�digo para escrever string
	syscall		# Escreve string		
lFimDecres:
	lw $a0, ($s1) # Carrega vetor[i]
	li $v0, 1 # C�digo para escrever inteiros
	syscall # Escreve inteiro
	li $a0, 32 # Carrega " "
	li $v0, 11 # C�digo para escrever caracter
	syscall # Escreve caracter
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lFimDecres	# if (i < n) goto loopFimOrdemDecrescente
	jr $ra					# retorno para a main
produto:
	move $s1, $s0	# Salva endere�o do vetor
	li $t1, 1	# produto
	li $t2, 0	# i		
lProduto:
	lw $t4, ($s1) # aux = vetor[i]
	mul $t1, $t1, $t4 # produto *= aux
	add $s1, $s1, 4 # vetor[i++]
	addi $t2, $t2, 1 # i++
	blt $t2, $t3, lProduto	# if (i < n) goto loopProdutoValores
	j fimProdutoValores			# goto fimProdutoValores	
fimProdutoValores:
	la $a0, produtoText	# Carrega endere�o da string
	li $v0, 4	# C�digo para escrever string
	syscall		# Escreve string
	move $a0, $t1	# Carrega o maior valor
	li $v0, 1	# C�digo para escrever inteiros
	syscall		# Escreve inteiro
	jr $ra		# Retorno para a main		
quantidadeCaracteres:
	la $a0, Arquivo # Carrega endere�o do arquivo
	li $v0, 13 # C�digo para abrir arquivo
	li $a1, 0 # Abrindo arquivo para leitura
	li $a2, 0 # Permiss�es padr�es do arquivo
	syscall # Abre o arquivo
	blt $v0, 0, erroAbreArquivo	# if ($v0 < 0) goto erroArquivo
	move $t0, $v0 # Salva o identificador do arquivo	
	li $t1, 0 # contador	
lQuantia:
	move $a0, $t0 # Carrega identificador do arquivo
	la $a1, buffer # Carrega endere�o do buffer
	li $a2, 1 # N�mero de caracteres a serem lidos
	li $v0, 14 # C�digo para ler um arquivo
	syscall # le o arquivo 
	beq $v0, $zero, fimQuantidadeCaracteres	# if ($v0 == $zero) goto fimQuantiadadeCaracteres
	addi $t1, $t1, 1 # contador++
	j lQuantia # goto loopQuantidadeCaracteres		
fimQuantidadeCaracteres:
	la $a0, numText	# Carrega endere�o da string
	li $v0, 4	# C�digo para escrever string
	syscall		# Escreve string
	move $a0, $t1	# Carrega o maior valor
	li $v0, 1	# C�digo para escrever inteiros
	syscall		# Escreve inteiro
	jr $ra		# Retorno para a main
	

	
