.data
    msg1: .asciiz "K: "
    msg2: .asciiz "N: "
    msg3: .asciiz "K^N = "
.text
main:
        li $v0, 4    
        la $a0, msg1 # Escreve "K: "
        syscall
        li $v0, 5   
        syscall # Le valor de k
        move $s0, $v0 # Armazena k em s0
        li $v0, 4  
        la $a0, msg2  
        syscall # Escreve "N: "
        li $v0, 5  
        syscall # Le valor de n
        move $s1, $v0  # Armazena n em s1
        li $v0, 4    
        la $a0, msg3 # Escreve "K^N = "
        syscall
        #MOVENDO PARAMETROS
        move $a0, $s0
        move $a1, $s1
        jal potencia # a0 ^ a1
        move $a0, $v0   # Move o resultado para impressão
        li $v0, 1
        syscall
        li $v0, 10   # codigo syscall para finalizar programa
        syscall
potencia:
    	bnez $a1, recursao 
    	# n for zero o resultado sera 1
    	li $v0, 1 # Retorna 1
    	jr $ra
recursao: # Se nao entra na recursao
        addi $sp, $sp, -4 # Armazena valor na stack
        sw $ra, 0($sp)       
       	subi $a1, $a1, 1      	
	jal potencia	
	mul $v0, $a0, $v0 # Multiplica a0 por ele mesmo	
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	# Resultado ja esta em v0
        jr $ra
