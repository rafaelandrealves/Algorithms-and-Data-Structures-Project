# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -g -Wall -ansi -pedantic -std=c99

# Sources

SOURCES = main.c util.c util.h

# Objects

OBJECTS = util.o

%.o: %.c

tuktuk: main.o util.o
	$(CC) $(CFLAGS) -o tuktuk main.o util.o

main.o: main.c util.h
	$(CC) -c $(CFLAGS) main.c

util.o: util.c util.h
	$(CC) -c $(CFLAGS) util.c