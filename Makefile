CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS =
SRCS = stack.c two_stacks.c
OBJS = $(SRCS:.c=.o)
TARGET = two_stacks

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
