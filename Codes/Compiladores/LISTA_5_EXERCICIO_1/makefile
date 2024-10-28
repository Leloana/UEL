# Nome do executável
TARGET = l5e1

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Arquivos de origem e objetos
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Regra padrão para compilar o programa
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets para evitar conflitos com arquivos de mesmo nome
.PHONY: all clean
