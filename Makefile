EXEC = calculadora_polaca
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
CFILES = pila.c calculadora_polaca.c strutil.c

all:
	$(CC) $(CFLAGS) $(CFILES) -o $(EXEC)

run: all
	./$(EXEC) < cal.txt

val: all
	valgrind $(VFLAGS) ./$(EXEC) < cal.txt

