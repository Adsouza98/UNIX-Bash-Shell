# Author: Andre D'Souza

# Variables of all object files
BIN = ./bin/
LIB = ./lib/
SRC = ./src/

# Override Default Variables
CC = gcc																	# Compiler
CFLAGS = -c -g -Wall --std=c11 -Iinclude 	# C Compiler Flags

# Defualt Rule
all: main.o funcSet1.o funcSet2.o funcSet3.o
	$(CC) $(BIN)main.o $(BIN)funcSet1.o $(BIN)funcSet2.o $(BIN)funcSet3.o -o $(BIN)myShell

main.o:
	$(CC) $(CFLAGS) -c $(SRC)main.c -o $(BIN)main.o

funcSet1.o:
	$(CC) $(CFLAGS) -c $(SRC)funcSet1.c -o $(BIN)funcSet1.o

funcSet2.o:
	$(CC) $(CFLAGS) -c $(SRC)funcSet2.c -o $(BIN)funcSet2.o

funcSet3.o:
	$(CC) $(CFLAGS) -c $(SRC)funcSet3.c -o $(BIN)funcSet3.o

# Cleaning Up All Artifacts
.PHONY: clean
clean:
	rm -f -r $(BIN)*

run:
	$(BIN)myShell

valgrind:
	valgrind --leak-check=yes $(BIN)myShell
