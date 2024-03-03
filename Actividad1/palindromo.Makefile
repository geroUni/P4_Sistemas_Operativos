# Makefile para palindromo_checker.c

# Compilador
CC = gcc

# Opciones del compilador
CFLAGS = -Wall -Wextra -std=c99

# Nombre del ejecutable
TARGET = palindromo_checker

# Archivos fuente
SRCS = palindromo_checker.c

all: $(TARGET)
	@echo "¡Finalizado!"

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
	@echo "Limpieza completada"
