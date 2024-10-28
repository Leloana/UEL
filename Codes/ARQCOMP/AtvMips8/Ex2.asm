.data
	Arquivo: .space 64
    	NewArq: .asciiz "ex2Arq.txt"
    	buffer: .asciiz " "
    	Ent: .asciiz "Insira o nome do arquivo no formato exemplo.txt: "
.text 
main:
	#============== ALOCANDO INPUT ===========
	li $v0, 4 
    	la $a0, Ent
    	syscall #Escreve "Digite nome do arquivo: "
    	li $v0, 8 
    	la $a0, Arquivo  
    	li $a1, 64 # Limita nome do arquivo em 64
    	syscall # Le o nome do arquivo
    	#=========================================
    	# É NECESSARIO REMOVER O '\n'
    	jal tamString # Retorna o tamanho da string a0 em v0
    	move $t2, $v0
    	addi $t2, $t2, -1 # Subtrai 1 ('\0')
    	add $t0, $t2, $a0 # t0 = endereco da String + indice fim
    	sb  $zero, ($t0) # substitui '\n' por 0
    	la $a0, Arquivo 
    	li $a1, 0 # Set do arquivo com modo leitura
    	li $v0, 13 # Abre o arquivo
    	syscall
	move $s0, $v0 # s0 armazenara o descriptor do arquivo de entrada	
	#================ PREPARA ARQUIVO DE SAIDA ================
	la $a0, NewArq # a0 guarda o endereco do arquivo de saida
    	li $a1, 1# Set do arquivo com modo escrita
    	li $v0, 13 # Abre o arquivo
    	syscall
    	move $s1, $v0	# s1 armazenara o descriptor do arquivo de saida   	
    	jal newAsteris # Funcao que substitui as vogais por *    	
	#================ FINALIZANDO PROGRAMA ================
fim:
        li $v0, 16 # Codigo de fechar arquivo
        move $a0, $s0 
        syscall # Fecha o arquivo de Entrada            
        li $v0, 16 # Codigo de fechar arquivo
        move $a0, $s1  
        syscall # Fecha o arquivo de saida    
    	li $v0, 10
    	syscall
tamString: 	
    	li $t0, 0 # t0 guardara o tamanho da string
   	move $t1, $a0 # t1 é a string a medir
lT:
        lb $t2, ($t1) # t2 = string[i]
        beqz $t2, fimTamanho # Se a string acabar ( elemento vazio) Acaba
        addi $t0, $t0, 1 # Aumenta 1 no tamanho
        addi $t1, $t1, 1 # Vai para proximo elemento da string
        j lT # retorna loop
fimTamanho:
    	move $v0, $t0 # v0 = tamanho da string
    	jr $ra   	
    	
newAsteris: # (s0 = descriptor arquivo, s1 = descriptor arquivoSaida)
	li $t1, '*' 
A:
	li $v0, 14 # Codigo para ler   
        move $a0, $s0  # a0 armazena o descriptor do arquivo de entrada
        la $a1, buffer # a1 é o buffer de leitura
        li $a2, 1 
        syscall	# Le arquivo        					
        blez $v0, retorno  # chegou ao fim do arquivo
        lb $t0, ($a1) # t0 recebe o caracter atual do buffer
        #============= CHECANDO SE O CARACTER EH VOGAL =================
        beq $t0, 'a', true
        beq $t0, 'A', true
        beq $t0, 'e', true
        beq $t0, 'E', true
        beq $t0, 'i', true
        beq $t0, 'I', true
        beq $t0, 'o', true
        beq $t0, 'O', true
        beq $t0, 'u', true
        beq $t0, 'U', true
itera:
	# BUFFER DE ESCRITA DEVE ACOMPANHAR O DE LEITURA 
        li $v0, 15 # Codigo para escrever   
        move $a0, $s1 # a0 armazena o descriptor do arquivo de Saida
        la $a1, buffer # Escrevo a1 (*)
        li $a2, 1 
        syscall						
        j A # retorna loop
true:	
        sb $t1, ($a1) # a1 recebe um *
        j itera        
retorno:
	jr $ra
	
