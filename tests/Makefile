# Makefile for test.c

# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic

# Target executable
TARGET = out
SRC = test.c ../chess.c

# Build target
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up
clean:
	rm -f $(TARGET)
