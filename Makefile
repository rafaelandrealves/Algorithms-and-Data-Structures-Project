# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -std=c99 -O3

# Sources
#
HSOURCES = src/util.h src/points.h src/tabuleiros.h src/acervo.h src/dijkstra.h src/moves.h src/defs.h
OSOURCES = util.o points.o tabuleiros.o acervo.o dijkstra.o moves.o main.o

%.o: %.c


tuktuk: $(OSOURCES)
	$(CC) $(CFLAGS) -o tuktuk $(OSOURCES)
	@echo ./tuktuk ready to execute!!

main.o: src/main.c $(HSOURCES)
	$(CC) -c $(CFLAGS) src/main.c


util.o: src/util.c $(HSOURCES)
	$(CC) -c $(CFLAGS) src/util.c

tabuleiros.o: src/tabuleiros.c $(HSOURCES)
	$(CC) -c $(CFLAGS) src/tabuleiros.c

points.o: src/points.c $(HSOURCES)
	$(CC) -c $(CFLAGS) src/points.c

moves.o: src/moves.c $(HSOURCES)
	$(CC) -c $(CFLAGS) src/moves.c

acervo.o: src/acervo.c $(HSOURCES)
	$(CC) -c $(CFLAGS) src/acervo.c

dijkstra.o: src/dijkstra.c $(HSOURCES)
	$(CC) -c $(CFLAGS) src/dijkstra.c

c:	tuktuk
	clear

clean:
	@echo Cleaning...
	rm -f *.o core tuktuk *~
	@echo Cleaned!!

cc:	clean c
