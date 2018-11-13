# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -std=c99 -g

# Sources

SOURCES = main.c util.c util.h defs.h tabuleiros.h moves.h
HSOURCES = defs.h util.h tabuleiros.h points.h moves.h
OSOURCES = main.o util.o tabuleiros.o points.o moves.o

# Objects

OBJECTS = util.o tabuleiros.o main.o

%.o: %.c

tuktuk: $(OSOURCES)
	$(CC) $(CFLAGS) -o tuktuk $(OSOURCES)

main.o: main.c $(HSOURCES)
	$(CC) -c $(CFLAGS) main.c

util.o: util.c $(HSOURCES)
	$(CC) -c $(CFLAGS) util.c

tabuleiros.o: tabuleiros.c $(HSOURCES)
	$(CC) -c $(CFLAGS) tabuleiros.c

points.o: points.c $(HSOURCES)
	$(CC) -c $(CFLAGS) points.c

moves.o: moves.c $(HSOURCES)
	$(CC) -c $(CFLAGS) moves.c


clean::
	rm -f *.o core tuktuk *~
