# Variáveis
CC = gcc
BISON = bison
FLEX = flex
CFLAGS = -Wall -Wextra -lm
BISON_FLAGS = -d
FLEX_FLAGS = 
EXEC = gerador

# Arquivos fontes
LEXER_SRC = lexico.l
PARSER_SRC = sintatico.y
AST_SRC = ast.c
HASH_SRC = hash.c
MIPS_SRC = MIPS.c
EVAL_SRC = eval.c
TRANSV_SRC = transv.c

# Arquivos gerados
SINTATICO_C = sintatico.tab.c
SINTATICO_H = sintatico.tab.h
LEXICO_C = lex.yy.c
OBJS = $(SINTATICO_C:.c=.o) $(LEXICO_C:.c=.o) $(HASH_SRC:.c=.o) $(AST_SRC:.c=.o) $(EVAL_SRC:.c=.o) $(MIPS_SRC:.c=.o) $(MATRIX_SRC:.c=.o) $(TRANSV_SRC:.c=.o)

# Regra principal
all: $(EXEC)

# Compilação do executável
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(CFLAGS)

# Compilação do Bison
$(SINTATICO_C) $(SINTATICO_H): $(PARSER_SRC)
	$(BISON) $(BISON_FLAGS) $(PARSER_SRC)

# Compilação do Flex
$(LEXICO_C): $(LEXER_SRC) $(SINTATICO_H)
	$(FLEX) $(FLEX_FLAGS) $(LEXER_SRC)

# Compilação dos arquivos .c em .o
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Limpeza
clean:
	rm -f $(EXEC) $(OBJS) $(SINTATICO_C) $(SINTATICO_H) $(LEXICO_C)

# Limpeza completa (inclui arquivos gerados pelo Bison e Flex)
distclean: clean
	rm -f $(LEXICO_C) $(SINTATICO_H)

# Rodar o programa
run: $(EXEC)
	./$(EXEC)
