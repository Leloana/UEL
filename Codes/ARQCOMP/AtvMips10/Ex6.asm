.data
	msg1: .asciiz "Digite n: "
	msg2: .asciiz "N-esimo número de Catalan.: "
	zero: .float 0.0
	um: .float 1.0
	dois: .float 2.0
.text
main:
        li $v0, 4        
        la $a0, msg1     
        syscall # Escreve "Digite n: "
        li $v0, 6 
        syscall # Le valor float
        mov.s $f1, $f0 # Armazena valor em f1
        li $v0, 4      
        la $a0, msg2   
        syscall # Escreve "N-esimo número de Catalan.: "
        jal catalan
        mov.s $f12, $f0 
        li $v0, 2
        syscall # Imprime retorno da funcao
fim:
        li $v0, 10 # Codigo syscall finalizar programa
        syscall
catalan:
	# Prepara stack
    	addi $sp, $sp, -8
        sw $ra, 0($sp)
        s.s $f2, 4($sp)    
        l.s $f7, um # Carrega 1 em f7
        mov.s $f0 ,$f7 # Move 1 para f0
        l.s $f6, zero # Carrega 0 em f6
        c.eq.s $f1 ,$f6 # Se f1 for zero
        bc1t fimCatalan # Finaliza
        mov.s $f2, $f1 # Move f1 para f2       
        sub.s $f1, $f1, $f7 # Subtrai 1 de f7
       	jal catalan # chamada recursiva       	
       	mov.s $f3, $f2	# f3 recebe f2     	
       	l.s $f8, dois # f9 recebe 2
       	#============= APLICANDO FORMULA=============
        add.s $f4, $f3, $f7# n+1
       	mul.s $f3, $f3, $f8# 2n
       	sub.s $f3, $f3, $f7# 2n-1
       	mul.s $f3, $f3, $f8# 2(2n-1)       	
       	div.s $f5, $f3, $f4# 2(2n-1)/(n+1)       
       	mul.s $f0, $f5, $f0       	
fimCatalan:
	# Recupera stack
	lw $ra, 0($sp)
	l.s $f2, 4($sp)
	addi $sp, $sp, 8
        jr $ra # retorna caller
        
