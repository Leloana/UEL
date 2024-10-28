.data
   	msg1: .asciiz "Digite n: "
    	msg2: .asciiz "Hiperfatorial de n = "
.text
main:
	li $v0, 4
        la $a0, msg1
        syscall # Escreve "Digite n: "
        li $v0, 5       
        syscall # Le o valor de n
        move $t0, $v0  # Armazena o valor lido em t0
        li $v0, 4      
        la $a0, msg2   
        syscall # Escreve  "Hiperfatorial de n = "
        move $a0, $t0
        jal hiperFatorial
        move $a0, $v0 
        li $v0, 1
        syscall # Imprime resultado do hiperfatorial
fim:
        li $v0, 10 #Comando para finalizar o programa
        syscall
hiperFatorial:
	#Organiza stack
    	addi $sp, $sp, -8
        sw $ra, 0($sp)
        sw $s0, 4($sp)
        # caso base
        li $v0 , 1
        beqz $a0 , fimFat
        move $s0, $a0 # Armazena valor de n em s0
        subi $a0, $a0, 1 # Subtrai 1 em n
       	jal hiperFatorial # Chamada recursiva
       	move $t0, $s0 # t0 recebe valor de n
       	li $a2, 1 # a2 recebe 1
pow:
	beqz $t0, fimPow # Se t0 for zero finaliza
	mul $a2, $a2, $s0 # Multiplica s0 e armazena em a2
	subi $t0, $t0, 1 # Subtrai 1 em n
    	j pow # volta pro loop
fimPow:
    	mul $v0, $a2, $v0 # Multiplica v0 	
fimFat:
	# Recupera stack
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	addi $sp, $sp, 8
    	jr $ra  
        
