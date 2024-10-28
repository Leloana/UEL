EXEC = gcc
CFLAGS = -fstack-protector-all -g -Wall
PROJECT_NAME = portugol
OBJETCS = main.o lexico.o sintatico.o pilha.o

$(PROJECT_NAME): $(OBJETCS)
	$(EXEC) $(CFLAGS) $(OBJETCS) -o $(PROJECT_NAME) -lm

main.o: main.c
	$(EXEC) $(CFLAGS) -c main.c

lexico.o: lexico.c lexico.h
	$(EXEC) $(CFLAGS) -c lexico.c

sintatico.o: sintatico.c sintatico.h
	$(EXEC) $(CFLAGS) -c sintatico.c

pilha.o: pilha.c pilha.h
	$(EXEC) $(CFLAGS) -c pilha.c

clear: 
	rm -f *.o
	rm -f $(PROJECT_NAME)
	rm -f saida.txt

# ./portugol < testes/teste_09.por > saida.txt
# diff saida.txt saidas_padrao/saida_teste_09.por.txt