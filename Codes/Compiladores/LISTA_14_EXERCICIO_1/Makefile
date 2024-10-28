FLEX=flex
BISON=bison
CC=gcc

PROGRAMA = l14e1
LEXICO = lexico.l
SINTATICO = sintatico.y

$(PROGRAMA): $(LEXICO) $(SINTATICO)
	$(FLEX) $(LEXICO)
	$(BISON) -d $(SINTATICO)
	$(CC) *.c -I. -o $(PROGRAMA)

clear:
	rm -f sintatico.tab.c
	rm -f sintatico.tab.h
	rm -f lex.yy.c
	rm -f $(PROGRAMA)
	rm saida.txt