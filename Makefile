# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -std=c99 -g

# Sources
#
HSOURCES = util.h points.h tabuleiros.h acervo.h dijkstra.h moves.h defs.h
OSOURCES = util.o points.o tabuleiros.o acervo.o dijkstra.o moves.o main.o

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

acervo.o: acervo.c $(HSOURCES)
	$(CC) -c $(CFLAGS) acervo.c

dijkstra.o: dijkstra.c $(HSOURCES)
	$(CC) -c $(CFLAGS) dijkstra.c


clean::
	rm -f *.o core tuktuk *~
