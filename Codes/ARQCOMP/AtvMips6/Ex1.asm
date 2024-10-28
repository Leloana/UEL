.data
	tamanho: .asciiz "Tamanho do vetor:"
	Ent1 : .asciiz "Elemento["
	Ent2 : .asciiz "]: "
	Ent3 : .asciiz " ocorre "
	Ent4 : .asciiz " vez(es)\n"
	newline: .asciiz "\n"
.text
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
	jal frequencia
saida:
	li $v0, 10
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
	
frequencia:
	move $t0, $a1
	move $t1, $t0
	li $t2, 0 # Contador
	li $t4, 0
	
	# FAZER VETOR AUXILIAR
	move $a0, $s1
	li $v0, 9
	syscall
	move $a3, $v0 # Alocar em a2
	move $t7, $a3
f:
	#=================================
	move $t5, $a3 # Zera endereco do vetor auxiliar
	l.d $f4, ($t1)	# Elemento atual	 
	li $t6, 0 # Contador
check:
	l.d $f6, ($t5) # Vetor auxiliar
	c.eq.d $f6, $f4
	bc1t pula
	
	addi $t6, $t6, 1 # Soma 1 no contador
	addi $t5, $t5, 8 # Vai para proximo elemento
	ble $t6, $t4 check # Se o elemento atual tiver posicao menor que o tamanho do vetor
	
	move $t3, $t0 # Guarda endereco do vetor
	li $t9, 0 # Contador de iguais
	li $t8, 0 # Contador do vetor
loop:
	#Percorrer vetor procurando elementos iguais
	l.d $f2 , ($t3) # Guarda primeiro endereco do vetor
	c.eq.d $f4, $f2 # Se f4 = f2 incrementa
	bc1t soma
	j false
soma:	
	addi $t9, $t9, 1 # Soma 1 no contador
false:
	addi $t3, $t3, 8 # Soma 8 no endereco ( Tamanho do float)
	addi $t8, $t8, 1 #Soma1 no contador
	blt $t8, $a2, loop #Se t8 < s0 go to l ( continua loop)
	
	#============= SAIDA ============
	l.d $f12, ($t1) # Carrega o valor atual
	li $v0, 3
	syscall
	la $a0, Ent3
	li $v0, 4
	syscall
	move $a0, $t9
	li $v0, 1
	syscall
	la $a0, Ent4
	li $v0, 4
	syscall
	#=================================
	s.d $f4, ($t7) # guardar o valor lido em vetor[i]
	addi $t7, $t7, 8 
	addi $t4, $t4, 1
pula:
	addi $t1, $t1, 8 # Soma 8 no endereco ( Tamanho do float)
	addi $t2, $t2, 1 #Soma1 no contador
	blt $t2, $a2, f #Se t2 < s0 go to l ( continua loop)
	
	move $v0, $t0
	jr $ra
	
	
	
	
	
