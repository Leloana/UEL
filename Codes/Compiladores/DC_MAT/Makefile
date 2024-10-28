# Compilador
CC = gcc
CFLAGS = -Wall

# Alvo final
dcmat: dcmat_parser.o lex.yy.o main.o dcmat.o
	$(CC) $(CFLAGS) -o dcmat dcmat_parser.o lex.yy.o main.o dcmat.o -lm

# Gera dcmat_parser.c e dcmat_parser.h a partir de dcmat.y
dcmat_parser.c dcmat_parser.h: dcmat.y
	bison -d dcmat.y -o dcmat_parser.c

# Gera lex.yy.c a partir de dcmat.l
lex.yy.c: dcmat.l dcmat_parser.h
	flex dcmat.l

# Compila os arquivos C
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

dcmat.o: dcmat.c
	$(CC) $(CFLAGS) -c dcmat.c

dcmat_parser.o: dcmat_parser.c
	$(CC) $(CFLAGS) -c dcmat_parser.c

# Limpeza dos arquivos gerados
clean:
	rm -f dcmat *.o dcmat_parser.c dcmat_parser.h lex.yy.c
