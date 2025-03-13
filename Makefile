CXX = g++
CC = gcc
CXXFLAGS = -Wall -Wextra -I../src -I/usr/include/gtest
CFLAGS = -Wall -Wextra -I../src
LDFLAGS = -lgtest -lgtest_main -pthread

LIB_TARGET = libdeque.a
TEST_TARGET = test_deque
PROG_TARGET = program

.PHONY: all lib test prog clean

all: lib test prog

lib: $(LIB_TARGET)

$(LIB_TARGET): ../src/Deque.c ../src/Deque.h
	$(CC) $(CFLAGS) -c ../src/Deque.c -o Deque.o
	ar rcs $(LIB_TARGET) Deque.o

test:
	$(CXX) $(CXXFLAGS) deque_test.cpp -x c ../src/Deque.c -o $(TEST_TARGET) $(LDFLAGS)

prog:
	$(CC) $(CFLAGS) -DBUILD_MAIN ../src/Deque.c -o $(PROG_TARGET)

clean:
	rm -f Deque.o $(LIB_TARGET) $(TEST_TARGET) $(PROG_TARGET)










