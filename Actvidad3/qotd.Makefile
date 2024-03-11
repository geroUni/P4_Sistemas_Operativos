# Makefile for compiling and building the qotd (Quote of the Day) program

# Specifies the C compiler to be used
CC = gcc

# Additional compiler flags to enable warnings and enforce C99 standard
CFLAGS = -Wall -Wextra -std=c99

# Name of the executable file
TARGET = qotd

# List of source files
SRCS = qotd.c

# Default goal: builds the executable file\
all: $(TARGET)
	@echo "Build completed successfully!"

# Rule for building the executable file from the source files
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for cleaning up the build artifacts
clean:
	rm -f $(TARGET)
	@echo "Cleanup completed successfully!"
