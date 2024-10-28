# MARCELO FERREIRA DE ALMEIDA
.data
	frase: .asciiz "ANA E MARIANA GOSTAM DE BANANA"   # Frase
	palavra: .asciiz "ANA"                            # Palavra a ser contada
	resultado: .asciiz "A palavra ocorre "            # Mensagem inicial
	resultado2: .asciiz " vezes na frase."            # Mensagem final

.text
main:
    # Inicializa��o de registradores
    li $t0, 0  # Contador de ocorr�ncias
    li $t1, 0  # �ndice para percorrer a frase
    li $t2, 0  # �ndice para percorrer a palavra

loop_frase:
    lb $t3, frase($t1)  # Carrega um byte da frase
    beqz $t3, fim_loop # Se o byte for zero (fim da string), termina o loop

    li $t2, 0   # Reinicia o �ndice da palavra
    move $t4, $t1   # Salva o �ndice atual da frase em $t4

loop_palavra:
    lb $t5, palavra($t2)    # Carrega um byte da palavra
    lb $t6, frase($t4)      # Carrega um byte correspondente da frase

    # Se a palavra terminou, incrementa o contador e avan�a o �ndice da frase
    beqz $t5, ocorrencia
    # Se os bytes n�o coincidirem, volta para o in�cio da palavra
    bne $t5, $t6, next_char

    # Avan�a para o pr�ximo caractere na palavra e na frase
    addi $t2, $t2, 1
    addi $t4, $t4, 1
    j loop_palavra

ocorrencia:
    addi $t0, $t0, 1# Incrementa o contador de ocorr�ncias

next_char:
    addi $t1, $t1, 1  # Avan�a para o pr�ximo caractere na frase
    j loop_frase

fim_loop:
    # Exibe o resultado
    li $v0, 4
    la $a0, resultado
    syscall

    # Exibe o n�mero de ocorr�ncias
    li $v0, 1
    move $a0, $t0
    syscall

    # Exibe a mensagem final
    li $v0, 4
    la $a0, resultado2
    syscall

    # Termina o programa
    li $v0, 10
    syscall
