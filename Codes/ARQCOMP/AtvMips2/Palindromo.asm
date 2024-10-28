.data
	ent1: .asciiz "Insira a string 1: "
	saida1: .asciiz "Nao eh palindromo"
	saida2: .asciiz "Eh palindromo"
	newline: .ascii "\n"
	str1: .space 100
.text
main: 
	la $a0 ent1 #Parametro: mensagem
	la $a1, str1 #Parametro: endereço da string
	jal leitura #Leitura (mensagem, string)
	
	la $a0, str1 #Parametro: endereço da string 1
	
	jal palindromo
	
	beqz $v0, naopal
	la $a0, saida2
	li $v0, 4
	syscall
	j final

naopal:
	la $a0, saida1
	li $v0, 4
	syscall
final:
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

palindromo:
	move $t0, $a0 #Armazena o endereço da string 1 em t0
	li $t1, 0
	add $t1, $t1, $t0
	li $t8, 0 #Tamanho string
	li $t9, 0 #quantia iguais
	
	lbu $t4, newline # $t4 = '\n'
loop:	
	lbu $t2, 0($t1)  # Caractere da primeira string
	beqz $t2, prox #Se tiver "\0" pula
	beq $t2, $t4, prox #Se tiver "\n" pula
	
	addi $t1, $t1, 1 #$t1 guarda o endereco
	addi $t8, $t8, 1 #$t1 guarda o tamanho da string1
	j loop
	
	
prox:#Marca o fim da string
	li $t2, 0 #counter
	li $t1, 0
	add $t1, $t0, $t8 #Endereco do ultimo char da string
	subi $t0, $t0, 1
comeco:
	lbu $t5, 0($t1) #Ultimo char da string
	lbu $t6, 0($t0) #Primeiro char da string
	
	bne $t5, $t6, count #Se os dois caracteres nao forem iguais vai para count
	addi $t9, $t9, 1 #Soma 1 no contador de iguais
count:
	addi $t2, $t2, 1 #Soma 1 no contador
	subi $t1, $t1, 1 #Subtrai 1 no endereco da palavra 1
	addi $t0, $t0, 1 #Soma 1 no endereco da palavra 1
	
	beq $t2, $t8, fim #se o contador for igual ao tamanho da palavra finaliza
	j comeco #volta ao loop
fim:	
	bne $t8, $t9, false #Se o numero de caracteres iguais for igual ao numero de caracteres é palindromo
true:
	li $v0, 1 #v0 recebe 1 caso verdadeiro
	j return
false:
	li $v0, 0 #v0 recebe 0 caso falso
return:
	jr $ra #Retorna para main
	
	
	
	
	
	
