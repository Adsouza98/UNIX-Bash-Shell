# Author: Andre D'Souza

# Variables of all object files
BIN = ./bin/
LIB = ./lib/
SRC = ./src/

# Override Default Variables
CC = gcc																	# Compiler
CFLAGS = -c -g -Wall -Wpedantic --std=gnu99 -Iinclude 	# C Compiler Flags

# Defualt Rule
all: myShell.o funcSet1.o funcSet2.o funcSet3.o testfile.o
	$(CC) $(BIN)myShell.o $(BIN)funcSet1.o $(BIN)funcSet2.o $(BIN)funcSet3.o -o $(BIN)myShell
	$(CC) $(BIN)testfile.o -o $(BIN)testfile

myShell.o:
	$(CC) $(CFLAGS) -c $(SRC)myShell.c -o $(BIN)myShell.o

funcSet1.o:
	$(CC) $(CFLAGS) -c $(SRC)funcSet1.c -o $(BIN)funcSet1.o

funcSet2.o:
	$(CC) $(CFLAGS) -c $(SRC)funcSet2.c -o $(BIN)funcSet2.o

funcSet3.o:
	$(CC) $(CFLAGS) -c $(SRC)funcSet3.c -o $(BIN)funcSet3.o

testfile.o:
	$(CC) $(CFLAGS) -c $(SRC)testfile.c -o $(BIN)testfile.o

# Cleaning Up All Artifacts
.PHONY: clean
clean:
	rm -f -r $(BIN)*

run:
	$(BIN)myShell

valgrind:
	valgrind --leak-check=yes $(BIN)myShell
