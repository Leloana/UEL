.data
	ent1: .asciiz "Insira a string 1: "
	ent2: .asciiz "Insira a string 2: "
	newline: .ascii "\n"
	str1: .space 100
	str2: .space 100
	str3: .space 200
.text
main: 
	la $a0 ent1 #Parametro: mensagem
	la $a1, str1 #Parametro: endereço da string
	jal leitura #Leitura (mensagem, string)
	
	la $a0, ent2 #Parametro: mensagem
	la $a1, str2 #Parametro: endereco da string
	jal leitura #Leitura (mensagem, string)
	
	la $a0, str1 #Parametro: endereço da string 1
	la $a1, str2 #Parametro: endereço da string 2
	la $a2, str3 #Parametro: endereço da string 3
	
	jal intercala #Intercala str1,str2,str3
	
	move $a0, $v0 #Move o retorno da string resultante
	li $v0,4 #Codigo de impressao da string
	syscall #Imprime
	
	li $v0, 10 #Codigo para finalizar programa
	syscall #Finaliza
	
leitura:
	li $v0, 4 #Codigo de impressao de string
	syscall #Imprime string
	
	move $a0, $a1 #Endereco da string para leitura
	li $a1, 100 #Numero maximo de caracteres
	
	li $v0, 8 #Codigo de leitura de string
	syscall #Le string
	
	jr $ra #Retorna para main
	
intercala:
	# =========== String 1 =============================
	move $t0, $a0 #Armazena o endereço da string 1 em t0
	
	# =========== String 2 =============================
	move $t1, $a1 #Armazena o endereço da string 2 em $t1
	
	# =========== String 3 =============================
	move $t2, $a2 #Armazena o endereço da string 3 em $t2
	
	li $t3, 0 #Inicia contador
	lbu $t4, newline # $t4 = '\n'
	
	
loop:
	lbu $t5, 0($t0)  # Caractere da primeira string
	beqz $t5, prox #Se tiver "\0" pula
	beq $t5, $t4, prox #Se tiver "\n" pula
	
	sb $t5, 0($t2) # Copia o caractere da primeira string para a string resultante
	addi $t0, $t0, 1 #Vai para proximo caracter de str1
	addi $t2, $t2, 1 #Vai para proximo caracter da str3
prox:
        lbu $t6, 0($t1) # Caractere da segunda string
	beqz $t6, prox1 #Se tiver "\0" pula
	beq $t6, $t4, prox1 #Se tiver "\n" pula
	
	sb $t6, 0($t2) #Armazena o caracter da str1 na str3
	addi $t2, $t2, 1 #Vai para proximo caracter da str3
	addi $t1, $t1, 1 #Vai para proximo caracter
prox1:	
	addi $t3, $t3, 1 #Soma 1 no contador
	
	bne $t3, 200,loop #Checa se contador ja chegou ao limite
fim:
	move $v0, $a2 # Endereço de vet para retorno
	jr $ra #Retorna para main

	
	
	
