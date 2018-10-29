# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -g -Wall -ansi -pedantic -std=c99

# Sources

SOURCES = main.c util.c util.h defs.h leitura_fich.h

# Objects

OBJECTS = util.o

%.o: %.c

tuktuk: main.o util.o leitura_fich.o
	$(CC) $(CFLAGS) -o tuktuk main.o util.o leitura_fich.o

main.o: main.c util.h defs.h leitura_fich.h
	$(CC) -c $(CFLAGS) main.c

util.o: util.c util.h defs.h leitura_fich.h
	$(CC) -c $(CFLAGS) util.c

leitura_fich.o: leitura_fich.c util.h defs.h
	$(CC) -c $(CFLAGS) leitura_fich.c


clean::
	rm -f *.o core a.out tuktuk *~