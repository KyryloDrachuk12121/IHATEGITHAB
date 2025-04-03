CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: convex

convex: main.o convex.o
	$(CC) $(CFLAGS) -o convex main.o convex.o -lm

main.o: main.c convex.h
	$(CC) $(CFLAGS) -c main.c -o main.o

convex.o: convex.c convex.h
	$(CC) $(CFLAGS) -c convex.c -o convex.o

clean:
	rm -f convex main.o convex.o


