# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -g -Wall -ansi -pedantic -std=c99

# Sources

SOURCES = main.c util.c util.h defs.h tabuleiros.h

# Objects

OBJECTS = util.o tabuleiros.o main.o

%.o: %.c

tuktuk: main.o util.o tabuleiros.o points.o
	$(CC) $(CFLAGS) -o tuktuk main.o util.o tabuleiros.o points.o

main.o: main.c util.h defs.h tabuleiros.h points.h
	$(CC) -c $(CFLAGS) main.c

util.o: util.c util.h defs.h tabuleiros.h points.h
	$(CC) -c $(CFLAGS) util.c

tabuleiros.o: tabuleiros.c defs.h util.h points.h
	$(CC) -c $(CFLAGS) tabuleiros.c

points.o: points.c defs.h util.h points.h
	$(CC) -c $(CFLAGS) points.c


clean::
	rm -f *.o core tuktuk *~