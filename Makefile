CC = gcc
CFLAGS = -O2 -Wall
TARGET = sort_benchmark

all: $(TARGET)

$(TARGET): testperf.c
	$(CC) $(CFLAGS) -o $(TARGET) testperf.c

run: $(TARGET)
	./$(TARGET) > results.txt
	@echo "Benchmark results saved to results.txt"

clean:
	rm -f $(TARGET) results.txt
