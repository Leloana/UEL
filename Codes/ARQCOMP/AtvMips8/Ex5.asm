.data
	filename_read: .asciiz "arquivo1.txt"
	filename_read2: .asciiz "arquivo2.txt"
	buffer: .asciiz " "
	vetor: .space  256 # Vetor para armazenar os caracteres lidos do arquivo1
	vetor2: .space  256 # Vetor para armazenar os caracteres lidos do arquivo2  
	saida1: .asciiz "\nTem uma sequencia de 5 ou mais caracteres"
	saida2: .asciiz "\nNao tem uma sequencia de 5 ou mais caracteres"
	newline: .asciiz "\n"
.text
main:
	# Abrir o arquivo para leitura
	li $v0, 13 # Codigo do sistema para abrir um arquivo
	la $a0, filename_read  # Carrega o endereço do nome do arquivo
	li $a1, 0 # Modo de abertura: leitura
	syscall
	move $s0, $v0 # Salva o descritor do arquivo em $s0
	la $t0, vetor
lendo1:
    	li $v0, 14 # Codigo para leitura do arquivo
	move $a0, $s0 # a0 recebe o descriptor do arquivo de entrada
	la $a1, buffer # $a1 caminha pelo arquivo
	li $a2, 1 # a2 é o tamanho de um caracter
	syscall # Le 1 caracter				   
	blez $v0, end_read1 # Se o caracter lido for nulo acaba
	lb $t2, ($a1) # t2 recebe o caracter lido
	sb $t2, 0($t0)
	addi $t0, $t0, 1
	j lendo1
end_read1:
	# Fechar o arquivo de leitura
	li $v0, 16 # Codigo do sistema para fechar um arquivo
	move $a0, $s0 # Passa o descritor do arquivo
	syscall
    	# Abrir o arquivo para leitura
	li $v0, 13 # Código do sistema para abrir um arquivo
	la $a0, filename_read2     # Carrega o endereço do nome do arquivo
	li $a1, 0 # Modo de abertura: leitura
	syscall
	move $s0, $v0 # Salva o descritor do arquivo em $s0
	la $t0, vetor2
lendo2:
    	li $v0, 14 # Codigo para leitura do arquivo
	move $a0, $s0 # a0 recebe o descriptor do arquivo de entrada
	la $a1, buffer # $a1 caminha pelo arquivo
	li $a2, 1 # a2 é o tamanho de um caracter
	syscall # Le 1 caracter				   
	blez $v0, end_read2 # Se o caracter lido for nulo acaba
	lb $t2, ($a1) # t2 recebe o caracter lido
	sb $t2, 0($t0)
	addi $t0, $t0, 1
	j lendo2
end_read2:
	# Fechar o arquivo de leitura
	li $v0, 16 # Código do sistema para fechar um arquivo
	move $a0, $s0 # Passa o descritor do arquivo
	syscall
    	la $a1, vetor # Vetor vindo do arquivo 1
	la $a2, vetor2 # Vetor vindo o arquivo 2
    	jal EncontraSequencia # Checa se tem uma sequencia igual entre os vetores 1 e 2
    	# Retorna 0 se nao tiver, e outro numero caso contrario
	beq $v0, 0, false    
	move $a0, $v0
	li $v0, 1
	syscall    
	li $v0, 4
	la $a0, saida1 # Escreve que ha uma sequencia
	syscall
	j fim
false:
	li $v0, 4
	la $a0, saida2 # Escreve que nao ha sequencia
	syscall
fim:
	li $v0, 10
	syscall    
EncontraSequencia: #(a1 e a2)
	# Funcao acaba ao acabar a1 ou ao encontrar uma sequencia
	move $t0, $a1 # String 1
	move $t1, $a2 # String 2
	li $t9, 0 # Contador de iguais
loop1:
	lb $t2, ($t0)
	beqz $t2, finaliza # Checa se o vetor 1 chegou ao fim
	move $t8, $t0 # t8 recebe endereco atual de t0
	move $t1, $a2 # t1 reseta seu enderecamento
loop2:
	lb $t2, ($t8) # t2 recebe atual de t8
	lb $t3, ($t1) # t3 recebe atual de t1	
	beqz $t3, sequenciaDiff # se t3 for nulo vai para proximo t0
	beq $t2, $t3, iguais # Se t2 == t3 goto iguais
	j diferente # Se nao goto diferente
iguais:
	addi $t9, $t9, 1 # Soma 1 em iguais
	addi $t8, $t8, 1 # Se for igual itera ambos
	addi $t1, $t1, 1 # soma 1 no endereco de t1
	beq $t9, 5, finaliza # Finaliza funcao
	j loop2
diferente:
	bne $t9, 0, sequenciaDiff # Se t9 != 0, estou no meio de uma sequencia
	# Se t9 = 0 quer dizer que a sequencia ainda nao comecou
	addi $t1, $t1, 1 # Se for diferente itera apenas em um
	j loop2	
sequenciaDiff:
	li $t9, 0 # Reseta o contador de iguais
	addi $t0, $t0, 1 # soma 1 no endereco de t0
	j loop1	# volta ao loop 
finaliza:
	blt $t9, 5, zerar
	j retorno
zerar:
	li $t9, 0 # zera valor de t9
retorno:
	move $v0, $t9 # Move quantidade de sequencia 
	jr $ra


	
	
	
