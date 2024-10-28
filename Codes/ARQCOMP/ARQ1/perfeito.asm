.data
	numero: .word 7 # Numero que sera analisado 
	contador: .word 1 # contador para loop
	soma: .word 0 #soma dos divisores
	Perfeito: .asciiz "É perfeito"
	notPerfeito: .asciiz "Nao é perfeito"

.text
	lw $t1, numero #Load no numero
	lw $t2, contador #Load do contador
	lw $t3, soma #Load da soma
loop:
	divu $t1, $t2 # Divide $t1 (dividendo) por $t2 (divisor)
        mfhi $t4 # Move o resto para $t4
	
	beqz $t4, somando # se t4 = 0 entao ele é divisor do numero
	j addContador #jump para add contador
	
somando:
	add $t3,  $t3, $t2 #soma o divisor do numero em soma
	
addContador:
	addi $t2, $t2, 1 #Soma 1 no contador
	beq $t1, $t2, imprimir #checa se o contador atingiu o limite ("numero")
	j loop #loop continua
	
imprimir:	
	beq $t1, $t3, perfeito #Checa se numero é perfeito
	j notperfeito #Caso nao seja perfeito

perfeito:
	li $v0, 4 #Sinaliza syscall para imprimir uma string					
	la $a0, Perfeito #Carrega o endereco de Perfeito em a0		
	syscall #Printa Perfeito no terminal com o texto "É perfeito"
	j exit #sai do codigo
	
notperfeito:
	li $v0, 4 #Sinaliza syscall para imprimir uma string					
	la $a0, notPerfeito #Carrega o endereco de notPerfeito em a0		
	syscall #Printa notPerfeito no terminal com o texto  "Nao é perfeito"
exit:
	li $v0, 10 # Código de serviço para sair do programa
        syscall
