# Makefile para palindromo_checker.c

# Compilador utilizado para construir el ejecutable
CC = gcc

# Opciones adicionales para el compilador
# -Wall: habilita la mayoría de las advertencias de compilación
# -Wextra: habilita advertencias de compilación adicionales
# -std=c99: especifica el estándar de C99 como el estándar de C a utilizar
CFLAGS = -Wall -Wextra -std=c99

# Nombre del ejecutable resultante
TARGET = palindromo_checker

# Archivos fuente de C que se van a compilar
SRCS = palindromo_checker.c

# Regla para construir el objetivo "all", que depende del objetivo $(TARGET)
all: $(TARGET)
	@echo "¡Finalizado!"

# Regla para construir el objetivo $(TARGET) a partir de los archivos fuente
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para eliminar el archivo ejecutable $(TARGET)
clean:
	rm -f $(TARGET)
	@echo "Limpieza completada"
