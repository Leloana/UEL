FLEX=flex
CC=gcc

PROGRAMA = l7e2
LEXICO = L7_Ex2.l

$(PROGRAMA): $(LEXICO)
	$(FLEX) $(LEXICO)
	$(CC) lex.yy.c $(LIBS) -o $(PROGRAMA)

clear:
	rm -f lex.yy.c
	rm -f $(PROGRAMA)