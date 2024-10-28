.data
    	msg1: .asciiz "Digite x em radianos: "
    	msg2: .asciiz "Quantos termos sua serie tera: "
    	msg3: .asciiz "cos("
	msg4: .asciiz "): "
    	var: .double 1.0
    	menosUm: .double -1.0
    	
.text
main:
	#============== INPUT ============================
        la $a0, msg1# carrega mensagem("Digite x (radianos): ")
        li $v0, 4# codigo syscall para imprimir string
        syscall
        li $v0, 7# codigo sycall ler double
        syscall						
        la $a0, msg2# carrega mensagem("Digite quantidade de termos: ")
        li $v0, 4 # codigo syscall para imprimir string
        syscall
        li $v0, 5# codigo syscall ler int
        syscall						
        move $s0, $v0# s0 = numero de termos (n)
        #==================================================
        jal serie
	#============== RESULTADO ==========================
        li $v0, 4# codigo syscall para imprimir string
        la $a0, msg3# carrega mensagem("Aproximacao de cos(")
        syscall						
        li $v0, 3# codigo sycall imprimir double
        mov.d $f12, $f0
        syscall	
        addi $v0, $0, 4	# codigo syscall para imprimir string
        la $a0, msg4# carrega mensagem("): ")
        syscall											
        li $v0, 3# codigo syscall imprimir double
        mov.d $f12, $f2
        syscall	
        #====================================================
saida:
        li $v0, 10# codigo syscall finalizar progama
        syscall					

serie:
        l.d $f2, var# resultado(f2) = 1.0
        l.d $f4, var  # termo(f4) = 1.0
        l.d $f14, menosUm # sinal(f14) = -1.0
        l.d $f12, menosUm# f12 = -1.0
        
        # for(i = 1; i <= $s0; i++)
        li $t0, 1 # i(t0) = 1
s:         
	#======================== CALCULO ==============================
	sll  $t1, $t0, 1# $t1 = 2*i       
	mtc1.d $t1, $f6
	cvt.d.w $f6, $f6 # f6 = (float)$t1
	add.d $f8, $f6, $f12# f8 = (2 * i - 1)
	mul.d $f10, $f0, $f0# numerador(f10) = x * x 
	mul.d $f6, $f6, $f8 # denominador(f6) = ((2 * i) * (2 * i - 1))
	div.d $f10, $f10, $f6  # f(10) = x * x / ((2 * i) * (2 * i - 1))
	mul.d $f4, $f4, $f10 # termo(f4) *= x * x / ((2 * i) * (2 * i - 1))

	mul.d $f10, $f14, $f4 # sinal(f14) * termo(f4)
	add.d $f2, $f2, $f10  # resultado(f2) += sinal(f14) * termo(f4)

	mul.d $f14, $f14, $f12 # sinal(f14) *= -1
	addi $t0, $t0, 1 # Incrementa contador
	blt $t0, $s0, s # Se o contador for menor que n continua
	#=================================================================
        jr $ra
        
