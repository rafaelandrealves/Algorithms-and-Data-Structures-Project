# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -g -Wall -ansi -pedantic -std=c99

# Sources

SOURCES = main.c util.c util.h defs.h tabuleiros.h

# Objects

OBJECTS = util.o

%.o: %.c

tuktuk: main.o util.o tabuleiros.o
	$(CC) $(CFLAGS) -o tuktuk main.o util.o tabuleiros.o

main.o: main.c util.h defs.h tabuleiros.h
	$(CC) -c $(CFLAGS) main.c

util.o: util.c util.h defs.h tabuleiros.h
	$(CC) -c $(CFLAGS) util.c

tabuleiros.o: tabuleiros.c defs.h util.h 
	$(CC) -c $(CFLAGS) tabuleiros.c


clean::
	rm -f *.o core a.out tuktuk *~