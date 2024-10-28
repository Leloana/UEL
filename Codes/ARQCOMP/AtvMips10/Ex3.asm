.data
    msg1: .asciiz "Digite n: "
    msg2: .asciiz "N DEVE SER POSITIVO!!\n"
    msg3: .asciiz "Combinacoes com as primeiras "
    msg4: .asciiz " letras do alfabeto:\n"
.text
main:
        li $v0, 4		 
        la $a0, msg1
        syscall	# Escreve "Digite n:"				
        li $v0, 5	 
        syscall	# Le valor de n					
        move $s0, $v0 # Armazena n em s0
        bgtz $s0, c # Checa se n eh valido (Deve ser positivo)
        # Caso o n for negativo
        li $v0, 4		# codigo syscall imprimir string
        la $a0, msg2
        syscall	# Escreve "N DEVE SER POSITIVO!!\n"					
        j fim # Encerra programa				       
c: # Caso n seja aceito
        move $a0, $s0 # aloca s0 bytes no vetor
        li $v0, 9 
        syscall	# Aloca vetor				
        move $s1, $v0 # Guarda vetor em s1
        li $t0, 0 # Inicia contador
vetLetras:  
        bge $t0, $s0,fimVet # Finaliza caso i seja maior que s0       
        addi $t2, $t0, 65 # t2 recebe as letras (62 é a letra 'A')
        add $t1, $s1, $t0 # t1 é o endereco do elemento atual do vetor
        sb $t2, 0($t1) # Armazena a letra atual no vetor     
        # Itera o contador 
        addi $t0, $t0, 1 
        j vetLetras 
fimVet:
        li $v0, 4 
        la $a0, msg3        
        syscall	#Escreve "Combinacoes com as primeiras "					
        li $v0, 1 
        move $a0 , $s0
        syscall	# Escreve o numero de letras a serem permutadas					
        li $v0, 4		 
        la $a0, msg4     
        syscall	# Escreve " letras do alfabeto:\n"	
        # PREPARA PARAMETROS					
        move $a0, $s1 # a0 eh o vetor		 
        li $a1, 0  # a1 eh 1
        move $a2, $s0 # a2 eh a quantia de letras
        jal permutar # Funcao que cria todas as permutaçoes e as escreve
fim:
        li $v0, 10 # codigo syscall finalizar programa
        syscall					    
permutar:  
        beq $a1, $a2, if_permutar # Se o a1 for igual ao a2 goto if_permutar
        j else_permutar	# Se nao goto else_permutar
if_permutar:
        move $t2, $a0 # t2 recebe o endereco das letras 
        li $t0, 0 # Inicia contador
print: 
        bge $t0, $a2, fimPrint # Se o i for maior que a quantia de letras finaliza
        add $t1, $t2, $t0 # &letras[i]
        lb  $a0, 0($t1) # a0 recebe a letra atual
        li $v0, 11  
        syscall	# Escreve a letra atual					
        #ITERA
        addi $t0, $t0, 1  
        j print 
fimPrint:
        li $v0, 11 
        li $a0, 10 
        syscall	# Escreve o pula linha					 
        j fimPermutar 
else_permutar:
        move $t0, $a1 # i vai receber a1 (Contador)
p:  
        bge $t0, $a2, fimPermutar # Se t0 for maior que a quantia  n de letras finaliza
        add $t1, $a0, $a1 # &letras[inicio]
        lb  $t2, 0($t1) # temp = letras[inicio]
        add $t3, $a0, $t0 # &letras[i]
        lb  $t4, 0($t3) # letras[i]
        sb  $t4, 0($t1) # letras[inicio] = letras[i]
        sb  $t2, 0($t3)  # letras[i] = temp
# Prepara a pilha de registradores para a recursao
        subi $sp, $sp, 20
        sw $ra, 0($sp)
        sw $a0, 4($sp)
        sw $a1, 8($sp)
        sw $a2, 12($sp)
        sw $t0, 16($sp)
        move $a0, $a0 # $a0 = $a0
        addi $a1, $a1, 1 # ITERA a1
        move $a2, $a2 # $a2 = $a2
        jal permutar
# Recupera os registradores da pilha
        lw $ra, 0($sp)
        lw $a0, 4($sp)
        lw $a1, 8($sp)
        lw $a2, 12($sp)
        lw $t0, 16($sp)
        addi $sp, $sp, 20
        add $t1, $a0, $a1 # &letras[inicio]
        lb  $t2, 0($t1)  # temp = letras[inicio]
        add $t3, $a0, $t0 # &letras[i]
        lb  $t4, 0($t3)  # letras[i]
        sb  $t4, 0($t1)  # letras[inicio] = letras[i]
        sb  $t2, 0($t3) # letras[i] = temp 
        #ITERA         
        addi $t0, $t0, 1 
	j p		 
fimPermutar:
        jr $ra					 
        
