.data
	Ent1: .asciiz "Informe a posição i: "
	ErrorMsg1: .asciiz "Erro ao abrir o arquivo"
	Arquivo: .asciiz "vetor.txt"
	buffer: .space 64
.text
main:
	#======= PREPARANDO DADOS ==========================
	la $a0, Ent1  
	li $v0, 4  
	syscall	 # Escreve string "Informe a posição i: "
	li $v0, 5  
	syscall	 # Le inteiro
	move $s0, $v0  
	la $a0, Arquivo 
	li $v0, 13 # Código para abrir arquivo
	li $a1, 0 # Abre arquivo para leitura
	li $a2, 0 # Permissões padrões do arquivo
	syscall	 # Abre o arquivo
	blt $v0, 0, erroAbreArquivo # if ($v0 < 0) goto erroArquivo
	move $t0, $v0# Salva o identificador do arquivo
	jr $ra	
	#FUNCAO PARA ACHAR E ALTERAR O VALOR DA POSICAO i DO ARQUIVO
	jal mudaValue # mudaValue (i, file_name)
	
mudaValue:	
	move $a0, $t0	
	la $a1, buffer	
	li $a2, 64
	li $v0, 14
	syscall	# Le o arquivo
	la $t2, buffer	# Carrega o endereço do buffer
	move $a0, $t0# Carrega o identificador do arquivo
	li $v0, 16
	syscall	# Fecha o arquivo
#CONTA QUANTOS ESPACOS TEM, CADA ESPACO INDICA UM NOVO ELEMENTO
quantiaEspacos:
	li $t7, 0
	beq $s0, $t7, convert	# se o t7 tiver na posicao escolhida goto convert	
Lespacos:
	add $t2, $t2, 1	# Buffer[i++]
	lb $t6, ($t2)	# Carrega byte
	beq $t6, 32, proximo# if ($t6 == 32) goto proximo
	beq $s0, $t7, charToInt	# if ($t7 == i) goto charToInt
	j Lespacos	
proximo:
	addi $t7, $t7, 1# controle++
	j loopContaEspacos# goto loopContaEspacos	
#QUANDO CHEGAR NA QUANTIDADE DE ESPACO = i CONVERTE VALOR DA POSICAO	
convert:
	li $s5, 0# aux = 0			
loop:
	lb $t5, ($t2)	# carrega byte
	beq $t5, 32, fimConvert# if ($t5 == 32) achei numero
	beq $t5, $zero, fimConvert
	#======= CONVERTENDO DE CHAR PARA INT  ========
	subi $t5, $t5, 48# char to int
	mul $s5, $s5, 10 
	add $s5, $s5, $t5 
	add $t2, $t2, 1	# prox
	j loop	# goto loop		
fimConvert:
	addi $s5, $s5, 1 # Faz a funcao de somar 1 na posic 	
#LOOP PARA ENCONTRAR POSICAO DO ELEMENTO E ESCREVE-LA NO 
#ARQUIVO SUBSTITUINDO O ANTIGO	
loopfimConvert:
	sub $t2, $t2, 1	 # Volta uma posic no buffer
	lb $t7, ($t2) 
	beq $t7, 32, abreArquivoEscrita	# se t7 for um espaco acaba
	beq $t7, $zero, abreArquivoEscrita# se t7 for um espaco vazio acaba
	div $s5, $s5, 10# divide por 10
	mfhi $t6 # resto
	addi $t6, $t6, 48# int to char
	sb $t6, ($t2)# armazena byte
	j loopfimConvert# goto acheiNumer
			
abreArquivoEscrita:
	la $a0, file_name# Carrega endereço do arquivo
	li $v0, 13# Código para abrir arquivo
	li $a1, 1# Abrindo arquivo para escrita
	syscall	# Abre o arquivo
	blt $v0, 0, erroAbreArquivo# if ($v0 < 0) goto erroArquivo
	move $t0, $v0# Salva o identificador do arquivo
	
	move $a0, $t0# Carrega identificador do arquivo
	la $a1, buffer# Carrega buffer
	li $v0, 15# Código para escrever no arquivo
	syscall	# Escreve no arquivo
	j encerraPrograma
		
erroAbreArquivo:
	la $a0, ErrorMsg1# Carrega o endereço da string
	li $v0, 4# Código para escrever string
	syscall	# Escreve string
	j encerraPrograma# goto encerraPrograma
	
encerraPrograma:
	li $v0, 10# Código para encerrar o programa
	syscall	# Encerra o programa
	
