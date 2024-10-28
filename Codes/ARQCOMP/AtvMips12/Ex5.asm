# MARCELO FERREIRA DE ALMEIDA
.data
	prompt: .asciiz "Digite valor: "      
	tri_msg:  .asciiz " eh triangular\n"   
	not_tri_msg: .asciiz " nao eh triangular\n"   
	divider: .word 2                     

.text
main:
    li $v0, 4  # Carrega a syscall 4 (imprimir string)
    la $a0, prompt      # Carrega o endereço da mensagem para $a0
    syscall

    li $v0, 5 # Carrega a syscall 5 (ler inteiro)
    syscall
    move $t0, $v0   # Move o valor lido para $t0

    li $t1, 1 # Inicializa $t1 com 1 (início do cálculo)
    li $t2, 1 # Inicializa $t2 com 1 (resultado do cálculo)

check_triangle:
    mult $t1, $t1   # Multiplica $t1 por $t1
    mflo $t3     # Move o resultado para $t3 (parte inferior do cálculo)
    add $t3, $t3, $t1   # Adiciona $t1 ao resultado anterior (parte superior do cálculo)
    lw $t4, divider     # Carrega o divisor
    div $t3, $t4  # Divide $t3 pelo divisor
    mflo $t3 # Move o resultado da divisão para $t3

    bgt $t3, $t0, not_triangle  # Se $t3 for maior que $t0, não é triangular
    beq $t3, $t0, is_triangle   # Se $t3 for igual a $t0, é triangular

    addi $t1, $t1, 1    # Incrementa $t1 por 1
    add $t2, $t2, $t1   # Adiciona $t1 a $t2
    j check_triangle # Volta ao início para a próxima iteração

is_triangle:
    li $v0, 1  # Carrega a syscall 1 (imprimir inteiro)
    move $a0, $t0 # Move $t0 (o valor lido) para $a0
    syscall

    li $v0, 4        # Carrega a syscall 4 (imprimir string)
    la $a0, tri_msg  # Carrega o endereço de tri_msg para imprimir
    syscall

    j exit  # Pula para o fim do programa

not_triangle:
    li $v0, 1 # Carrega a syscall 1 (imprimir inteiro)
    move $a0, $t0  # Move $t0 (o valor lido) para $a0
    syscall

    li $v0, 4  # Carrega a syscall 4 (imprimir string)
    la $a0, not_tri_msg  # Carrega o endereço de not_tri_msg para imprimir
    syscall

    j exit   # Pula para o fim do programa

exit:
    li $v0, 10   # Carrega a syscall 10 (sair do programa)
    syscall
