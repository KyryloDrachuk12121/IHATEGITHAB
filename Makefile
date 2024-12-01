CC = gcc
CFLAGS = -Wall -std=c99
SOURCES = Hw7.2.c Source1.c
HEADERS = Header1.h
TARGET = Hw7.2

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) 
