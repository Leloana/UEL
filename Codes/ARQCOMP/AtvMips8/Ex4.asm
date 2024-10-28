.data
    Arquivo: .asciiz "matriz.txt"
    NewArq: .asciiz "matrizsaida.txt"
    espaco: .asciiz " "
    enter: .asciiz "\r\n"
    buffer: .asciiz " "
    
.text
main:
	#=============== PREPARANDO ARQUIVO DE LEITURA =============
        li $v0, 13	# codigo abertura arquivo
        la $a0, Arquivo # carrega endereco do arquivo
        li $a1, 0       # modo somente leitura    
        syscall
        move $s0, $v0	# s0 = descriptor arquivo
        #========== LENDO PRIMEIRA LINHA DO ARQUIVO==========
        jal Lint # Funcao para ler 1 inteiro da matriz
        move $s1, $v0 # s1 eh o numero de colunas da matriz
        jal Lint
        move $s2, $v0 # s2  eh o numero de linhas da matriz
        jal Lint
        move $s3, $v0 # s3 eh o numero de elementos anulados da matriz
	#Calculando numero de elementos da matriz
        mul $t0, $s1, $s2 # t0 = linha * coluna
        mul $t0, $t0, 4 # t0 = t0 * sizeof(int)

        move $a0, $t0 # a0 recebe o tamanho de bytes da matriz
        addi $v0, $0, 9	 # Aloca a memoria da matriz
        syscall					
        move $a3, $v0 # Matriz ficara em a3
        move $a2, $s2 # a2 recebe o numero de colunas da matriz
        
        li $t0, 0 # Inicia contador
matrizLinha:  
	bge $t0, $s1, fimLinha # Se t0 maior que linhas finaliza 
	li $t1, 0 # contador de colunas
matrizColuna:  
	bge $t1, $s2, fimColuna   # Se t1 maior que colunas finaliza 
	jal indice # &matriz[i][j]
	li $t2, 1  # Inicia t2 com 1
	# v0 é o endereco de retorno da matriz
	sw $t2, ($v0) # matriz[i][j] recebe 1
            
	addi $t1, $t1, 1 # Soma no contador da coluna
	j matrizColuna  
fimColuna:
	addi $t0, $t0, 1 # Soma no contador da linha
	j matrizLinha 
fimLinha:
        li $t9, 0 # Inicia t9 com 0
anularElementos: 
	#====================== ANULANDO MATRIZ =================================
	bge $t9, $s3, fimAnulada # se i for maior que numero de anuladas acabas
	jal Lint # Le o '\n', como nao é numero, o buffer se move sem escrever nada
	jal Lint # Le a linha a ser anulada          
	move $t0, $v0  # t0 recebe Linha anulada
	jal Lint # Le a culuna a ser anulada
	move $t1, $v0  # t1 recebe coluna anulada
	move $a2, $s2  # a2 recebe o numero de colunas
	jal indice     # Calculo o indice a ser anulado usando t0 e t1
	sw $zero, ($v0) # matriz[i][j] = 0
	addi $t9, $t9, 1 # itera no contador
	j anularElementos  
fimAnulada:
        li $v0, 16
        move $a0, $s0
        syscall # Fecha o arquivo de leitura           
        #=============== PREPARANDO ARQUIVO DE ESCRITA =============
        li $v0, 13 # Abre o arquivo de escrita
        la $a0, NewArq # carrega endereco do arquivo
        li $a1, 1 # somente escrita
        syscall
        move $s0, $v0 # s0 sera o descriptor do arquivo de saida
        
        li $t0, 0 # Inicia contador com 0
impMatrizLinha: 
	bge $t0, $s1, fimImpressaoLinha # Se t0 maior que linhas finaliza 
	li $t1, 0 # contador de colunas
impMatrizColuna: 
	bge $t1, $s2, fimImpressaoColuna # Se t0 maior que colunas finaliza 
	move $a2, $s2 # a2 = n_anulada
	jal indice # Calcula o indice do elemento atual
	lw $a0, ($v0) # a0 recebe o elemento atual da matriz
	jal imprimirElemento # a0 é impresso na matriz de saida 
	li $v0, 15 # Codigo escrita em arquivo
	la $a1, espaco # a1 recebe espaco
	li $a2, 1 # a2 recebe o tamanho de 1 caracter
	syscall									     
	addi $t1, $t1, 1 # Soma no contador das colunas
	j impMatrizColuna 
fimImpressaoColuna:
	li $v0, 15  # codigo escrita em arquivo
	la $a1, enter # Pula de linha
	li $a2, 2 # a2 recebe o tamanho de 2 caracteres
	syscall	
	addi $t0, $t0, 1 # Soma no contador de linhas
	j impMatrizLinha 
fimImpressaoLinha:
        li $v0, 16 
        move $a0, $s0 
        syscall # Fecha arquivo de escrita          
        li $v0, 10 
        syscall	       
indice: # (t0 = i, t1 = j, a2 = numColuna, a3 = endereco da matriz)
        mul $v0, $t0, $a2  
        add $v0, $v0, $t1  
        sll $v0, $v0, 2 
        add $v0, $v0, $a3      
        jr $ra # retorna endereco da matriz       
Lint:
        li $t1, 0 # Inicializa t0
        li $t3, 48 # Guarda o valor do caracter '0'
        li $t4, 57 # Guarda o valor do caracter '9'
l:
	li $v0, 14 # Codigo para leitura do arquivo
	move $a0, $s0 # a0 recebe o descriptor do arquivo de entrada
	la $a1, buffer # $a1 caminha pelo arquivo
	li $a2, 1 # a2 é o tamanho de um caracter
	syscall # Le 1 caracter				   
	blez $v0, fimLeit # Se o caracter lido for nulo acaba
	lb $t2, ($a1) # t2 recebe o caracter lido
	blt $t2, $t3, fimLeit # se t2 for menor que 0 acaba (Nao eh numero)
	bgt $t2, $t4, fimLeit # se t2 for maior que 9 acaba (Nao eh numero)
	#CONVERTE O VALOR DE CHAR PARA INT
	sub $t2, $t2, $t3  # subtrai o valor ASCII '0'
	mul $t1, $t1, 10   # multiplica o acumulador por 10
	add $t1, $t1, $t2  # adiciona o digito ao acumulador
	j l 
fimLeit:
        move $v0, $t1 # Retorna t1
        jr $ra	
imprimirElemento: 
        subi $sp, $sp, 4  
        sw $ra, ($sp)     
        la $a1, buffer # a1 é o buffer do arquivo 
	li $v0, 0 # v0 = 0
	li $t2, 0 # t2 = 0		
	jal convertInt	
	li $v0, 15 # Codigo para escrever no arq
	move $a0, $s0 # a0 é o descriptor do arquivo de escrita
	la $a1, buffer # a1 é o buffer do arquivo
	move $a2, $v0 # a2 = tamanho
	syscall									
        lw $ra, ($sp) 	 # recupera retorno 
        addi $sp, $sp, 4 # libera espaco pilha
        jr $ra            		
convertInt: # a0 = n
	div $a0, $a0, 10 # n recebe n/10
	mfhi $t3 # t3 guarda o resto da divisao
	subi $sp, $sp, 4 # Aloca espaço para 1 registrador
	sw $t3, ($sp) # Armazena o resto na pilha
	addi $v0, $v0, 1 # Soma o contador dos digitos
	bnez $a0, convertInt # Se n!= 0 goto convertInt
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