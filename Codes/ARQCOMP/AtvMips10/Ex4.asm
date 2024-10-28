.data
	msg1: .asciiz "Digite n: "
	msg2: .asciiz "Digite b: "
	msg3: .asciiz "Digite a: "
	msg4: .asciiz " primeiros multiplos de a e/ou b: "
.text
main:
        li $v0, 4   
        la $a0, msg1
        syscall # Escreve "Digite n"
        li $v0, 5        
        syscall # Le valor de n
        move $s0, $v0 # Armazena  valor de n em s0
        li $v0, 4       
        la $a0, msg2 
        syscall # Escreve "Digite b"
        li $v0, 5       
        syscall # Le valor de b
        move $s2, $v0   # Armazena  valor de n em s2
        li $v0, 4     
        la $a0, msg3  
        syscall # Escreve "Digite a"
        li $v0, 5       # codigo syscall ler inteiro
        syscall # Le valor de a
        move $s1, $v0  # Armazena  valor de a em s1
        li $v0, 1
        move $a0, $s0
        syscall # Escreve o valor de n
        li $v0, 4
        la $a0, msg4
        syscall # Escreve "primeiros multiplos de a e/ou b:"
        jal primeirosMultiplos 
fim:   
        li $v0, 10      # codigo syscall finalizar programa
        syscall    
primeirosMultiplos:
	li $t0, 1 #Inicia multiplos
pM:
	blez $s0, fimMul # Se s0 for zero acaba
	div $t0, $s1 # Divide possivel multiplo por s1
	mfhi $t1 # Guarda resto em t1
	beqz $t1, multiplo # Se o resto for zero eh multiplo
	div $t0, $s2  # Se nao for multiplo de a verifica se eh multiplo de b
	mfhi $t1 # Guarda resto em t1
        beqz $t1, multiplo # Se o resto for zero eh multiplo
itera:
        addi $t0, $t0, 1 # Incrementa 1 no possivel multiplo
        j pM  
multiplo:
	move $a0, $t0 
	li $v0, 1
	syscall # Imprime valor do multiplo
	li $a0, 32 
	li $v0, 11
	syscall # Imprime um espaço
	subi $s0, $s0, 1 # Subtrai 1 do n
	j itera
fimMul:
	jr $ra
        
