CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: geometry.o

geometry.o: geometry.c geometry.h
	$(CC) $(CFLAGS) -c geometry.c

clean:
	rm -f *.o
