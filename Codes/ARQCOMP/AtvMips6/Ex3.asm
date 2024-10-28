.data
	quantAlunos: .asciiz "Digite a quantidade de alunos:"
	Ent1 : .asciiz "Aluno["
	Ent2 : .asciiz "] Nota["
	Ent3 : .asciiz "]: "
	mAluno : .asciiz "Media do aluno "
	mAluno1 : .asciiz " = "
	mSala : .asciiz "Media da sala = "
	passaram: .asciiz " aluno(s) passou(passaram)"
	naoPassaram: .asciiz " aluno(s) nao passou(passaram)"
	newline: .asciiz "\n"
	zero: .double 0.0
	tres: .double 3.0
	seis: .double 6.0
.text
main:
	li $s0, 0 # Quantidade de alunos (Linhas)
	li $s1, 0 # Quantidade de bytes a alocar
	li $s2, 3 # Quantidade de notas (Colunas)
	la $a0, quantAlunos
	li $v0, 4
	syscall # Escreve "Digite a quantidade de alunos:"
	li $v0, 5 # Codigo para ler inteiro
	syscall
	move $s0, $v0 # Armazena a quantidade de alunos em s0
	li $t0, 8 # 8 é o tamanho do float
	mult $s0, $t0
	mfhi $s1 # s1 = s0 * 8 
	move $a0, $s1 # Alocar a memoria
	li $v0, 9
	syscall
	move $a1, $v0 # Endereco da matriz comecará em a1
	jal leitura
	jal medias
saida:
	li $v0, 10
	syscall
	
indice:
	mul $v0, $t0, $s2 # i * ncol
	add $v0, $v0, $t1 # (i * ncol) + j
	sll $v0, $v0, 3 # [(i *ncol) + j] * 8 (float)
	add $v0, $v0, $a1 # Soma o endereço base de mat
	jr $ra # Retorna

leitura:
	subi $sp, $sp, 4 # Abre Espaco na stack
	sw $ra, ($sp) # Guarda retorno na stack
	move $t0, $a1 # Armazena o endereco da matriz em t0
	li $t0, 0 # Inicia i = 0
	li $t1, 0 # inicia j = 0
l:
	#=================INTERFACE====================
	la $a0, Ent1 
	li $v0, 4
	syscall
	move $a0, $t0
	li $v0, 1
	syscall
	la $a0, Ent2
	li $v0, 4
	syscall
	move $a0, $t1
	li $v0, 1
	syscall
	la $a0, Ent3
	li $v0, 4
	syscall
	#==============================================
	
	li $v0, 7 # Codigo para ler float
	syscall
	#Float fica armazenado em f0
	jal indice
	s.d $f0, ($v0) # guardar o valor lido em vetor[i]
	
	#================= ITERANDO ==================
	addi $t1, $t1, 1 # Vai para proxima coluna (Nota do Aluno atual)
	blt $t1, $s2, l # Se a quantidade do contador < colunas
	addi $t0, $t0, 1 # Vai para proxima linha (Aluno)
	li $t1, 0 # Zera as colunas ( Vai par a primeira nota do proximo aluno)
	blt $t0, $s0, l # Se a quantidade do contador < linhas
	li $t0, 0 # Zera linhas
	#=============================================
	lw $ra, ($sp) # Resgata retorno da stack
	addi $sp, $sp, 4 # Fecha o espaco da stack
	
	move $v0, $a1 # Move o endereco da matriz para retorno
	jr $ra

medias:
	subi $sp, $sp, 4 # Abre Espaco na stack
	sw $ra, ($sp) # Guarda retorno na stack
	move $t0, $a1 # Armazena o endereco da matriz em t0
	li $t0, 0 # Inicia i = 0
	li $t1, 0 # inicia j = 0
	li $t2, 0 # Alunos que passaram
	l.d $f4, zero # Media aluno
	l.d $f6, zero # Media sala
	l.d $f8, tres
	mtc1 $s0, $f14
	cvt.d.w $f14, $f14 # f7 guarda a quantidade de alunos em double
	l.d $f10, seis
m:
	jal indice
	l.d $f2, ($v0) # Acessa elemento atual
	add.d $f4, $f4, $f2 # Soma a nota atual a soma das notas
	#================= ITERANDO ==================
	addi $t1, $t1, 1 # Vai para proxima coluna (Nota do Aluno atual)
	blt $t1, $s2, m # Se a quantidade do contador < colunas
	
	div.d $f4, $f4, $f8 # Divide por 3 ( sao 3 notas)
	
	#======= Escreve a media do aluno atual ======
	la $a0, mAluno
	li $v0, 4
	syscall
	move $a0, $t0
	li $v0, 1
	syscall
	la $a0, mAluno1
	li $v0, 4
	syscall
	mov.d $f12, $f4
	li $v0, 3
	syscall
	la $a0, newline
	li $v0, 4
	syscall
	#=============================================
	#Checa se aluno passou
	c.lt.d $f4, $f10 # Se a media do aluno for menor que 6
	bc1t naoPassou
	addi $t2, $t2, 1# Add 1 nos que passarao
naoPassou:	
	add.d $f6, $f6, $f4 # A media da sala recebe a media do aluno
	#Itera novamente
	l.d $f4, zero # Zera a media do aluno
	addi $t0, $t0, 1 # Vai para proxima linha (Aluno)
	li $t1, 0 # Zera as colunas ( Vai par a primeira nota do proximo aluno)
	blt $t0, $s0, m # Se a quantidade do contador < linhas
	li $t0, 0 # Zera linhas
	#Checa a media da sala
	div.d $f6, $f6, $f14 # A media da sala = soma/ quantidade de alunos
	la $a0, mSala
	li $v0, 4
	syscall
	mov.d $f12, $f6
	li $v0, 3
	syscall #Escreve valor da media
	#=============================================
	lw $ra, ($sp) # Resgata retorno da stack
	addi $sp, $sp, 4 # Fecha o espaco da stack
	la $a0, newline
	li $v0, 4
	syscall
	#Aprovados
	move $a0, $t2
	li $v0, 1
	syscall
	la $a0, passaram
	li $v0, 4
	syscall
	la $a0, newline
	li $v0, 4
	syscall
	#Reprovados
	sub $t2, $s0, $t2 # t2 = alunos totais - nao passaram
	move $a0, $t2
	li $v0, 1
	syscall
	la $a0, naoPassaram
	li $v0, 4
	syscall
	
	move $v0, $a1 # Move o endereco da matriz para retorno
	jr $ra