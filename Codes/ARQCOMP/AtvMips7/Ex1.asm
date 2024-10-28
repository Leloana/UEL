.data
	tamanho: .asciiz "Tamanho do vetor:"
	Ent1 : .asciiz "Elemento["
	Ent2 : .asciiz "]: "
	newline: .asciiz "\n"
	z: .double 0.0
	menor_double: .double -1.7976931348623157e+308
	textSoma: .asciiz "A maior soma de segmento é: "
	primeiro: .asciiz "\nComeco do segmento: "
	ultimo: .asciiz "\nFinal do segmento: "
.text
main:
	# s0 sera o tamanho do vetor
	# s1 sera o tamanho do vetor vezes 8 
	la $a0, tamanho
	li $v0, 4
	syscall
	
	li $v0, 5
	syscall
	move $s0, $v0 # Armazena quantidade de elementos do vetor
	
	li $t0, 8
	mult $s0, $t0 # Multiplica n por 8 ( tamanho do float )
	mflo $s1 # Guarda o resultado em s1
	
	li $v0, 9 # Codigo para alocar memoria
	move $a0, $s1 # Quantidade de memoria a alocar
	syscall
	move $a1, $v0 # Aloca a memoria do vetor em a1
	
	move $a2, $s0
	jal leitura
	
	move $a1, $v0
	move $a2, $s0
	jal escrita
	
	move $a1, $v0
	move $a2, $s0
	jal segmento
saida:
	li $v0 10
	syscall

leitura:
	move $t0, $a1
	move $t1, $t0
	li $t2, 0 # Contador
l:# Comeca loop
	#========== Interface ============
	la $a0, Ent1 # String 1
	li $v0, 4
	syscall
	move $a0, $t2 # Posicao
	li $v0, 1
	syscall
	la $a0, Ent2 # String 2
	li $v0, 4
	syscall
	#================================
	li $v0, 7
	syscall	# ler: vetor[i]
	s.d $f0, ($t1) # guardar o valor lido em vetor[i]
	addi $t1,$t1, 8 # Soma 4 no endereco do vetor( vai para proximo elemento)
	addi $t2,$t2, 1
	blt $t2, $a2, l # Se t2 < s0 go to l ( continua loop)
	
	move $v0, $t0 # Coloca o endereco do vetor para retorno
	jr $ra

escrita:
	move $t0, $a1
	move $t1, $t0
	li $t2, 0 # Contador
e: #Comeca loop
	#====== ESCREVENDO=======
	 # Carregar valor do vetor para $f12
    	l.d $f12, ($t1)
	li $v0, 3
	syscall	# print: vetor[i]
	li $a0, 32
	li $v0, 11
	syscall
	#=========================
	addi $t1, $t1, 8 # Soma 8 no endereco ( Tamanho do float)
	addi $t2, $t2, 1 #Soma1 no contador
	blt $t2, $a2, e #Se t2 < s0 go to l ( continua loop)
	
	la $a0, newline
	li $v0, 4
	syscall
	
	move $v0, $t0
	jr $ra
	
segmento:
	move $t0, $a1
	move $t1, $t0
	li $t2, 0 # Contador
	l.d $f4, menor_double # f4 sera a maior soma do segmento
	l.d $f8, z # f8 sera o ultimo elemento do segmento
	l.d $f14, z # f14 sera o primeiro elemento do segmento
s: #Começa loop
	l.d $f2, ($t1) # Carrega elemento atual da sequencia em f2
	#F2 guarda o valor da partida do segmento
iniciaSeg:
	move $t0, $a1
	li $t4, 0 # Contador do segmento
	add $t4, $t4, $t2 # Parte do elemento atual
	li $t5, 8 
	mult $t4, $t5 # Multiplica o valor por 8
	mflo $t5
	add $t0, $t0, $t5 # Soma no endereco para que o vetor inicie no atual
	l.d $f6, z # f6 sera a soma atual do segmento
seg:
	l.d $f10, ($t0) # Carrega elemento atual da sequencia em f6
	add.d $f6, $f6, $f10 # f6 sera a soma atual
	
	c.le.d $f4, $f6 # Se o valor atual do segmento for maior que o valor 
	bc1t troca #maior registrado, atualiza o maior registrado
	j itera
troca:
	mov.d $f4, $f6 # Atualiza o valor do maior
	mov.d $f8, $f10 # Guarda o comeco do segmento
	mov.d $f14, $f2 # Guarda o final do segmento
itera:	
	addi $t0, $t0, 8 # Soma 8 no endereco ( Tamanho do float)
	addi $t4, $t4, 1 #Soma1 no contador
	blt  $t4, $a2, seg #Se t2 < s0 go to l ( continua loop)
	
	addi $t1, $t1, 8 # Soma 8 no endereco ( Tamanho do float)
	addi $t2, $t2, 1 #Soma1 no contador
	blt $t2, $a2, s #Se t2 < s0 go to l ( continua loop)
	#=============== RESULTADO ========================
	li $v0, 4
	la $a0, textSoma 
	syscall# Escreve  A maior soma de segmento é:
	mov.d $f12, $f4
	li $v0, 3
	syscall# Escreve o valor da maior soma de segmento
	li $v0, 4
	la $a0, primeiro 
	syscall#Escreve Comeco do segmento:
	mov.d $f12, $f14
	li $v0, 3
	syscall #Escreve o valor do comeco de segmento
	li $v0, 4
	la $a0, ultimo 
	syscall # Final do segmento:
	mov.d $f12, $f8
	li $v0, 3
	syscall #Escreve o valor do final de segmento
	#====================================================
	move $v0, $a1
	jr $ra
	
