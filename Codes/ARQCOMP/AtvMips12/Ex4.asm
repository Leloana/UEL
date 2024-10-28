# MARCELO FERREIRA DE ALMEIDA
.data
	frase: .asciiz "ANA E MARIANA GOSTAM DE BANANA"   # Frase
	palavra: .asciiz "ANA"                            # Palavra a ser contada
	resultado: .asciiz "A palavra ocorre "            # Mensagem inicial
	resultado2: .asciiz " vezes na frase."            # Mensagem final

.text
main:
    # Inicialização de registradores
    li $t0, 0  # Contador de ocorrências
    li $t1, 0  # Índice para percorrer a frase
    li $t2, 0  # Índice para percorrer a palavra

loop_frase:
    lb $t3, frase($t1)  # Carrega um byte da frase
    beqz $t3, fim_loop # Se o byte for zero (fim da string), termina o loop

    li $t2, 0   # Reinicia o índice da palavra
    move $t4, $t1   # Salva o índice atual da frase em $t4

loop_palavra:
    lb $t5, palavra($t2)    # Carrega um byte da palavra
    lb $t6, frase($t4)      # Carrega um byte correspondente da frase

    # Se a palavra terminou, incrementa o contador e avança o índice da frase
    beqz $t5, ocorrencia
    # Se os bytes não coincidirem, volta para o início da palavra
    bne $t5, $t6, next_char

    # Avança para o próximo caractere na palavra e na frase
    addi $t2, $t2, 1
    addi $t4, $t4, 1
    j loop_palavra

ocorrencia:
    addi $t0, $t0, 1# Incrementa o contador de ocorrências

next_char:
    addi $t1, $t1, 1  # Avança para o próximo caractere na frase
    j loop_frase

fim_loop:
    # Exibe o resultado
    li $v0, 4
    la $a0, resultado
    syscall

    # Exibe o número de ocorrências
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
