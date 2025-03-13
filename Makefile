CXX       = g++
CC        = gcc
CXXFLAGS  = -Wall -g -std=c++14 -I../src
CFLAGS    = -Wall -g -std=c11   -I../src
TEST_TARGET = randomized_queue_test
TEST_OBJS = randomized_queue_test.o ../src/RandomizedQueue.o

all: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS) -lgtest -lpthread

randomized_queue_test.o: randomized_queue_test.cpp ../src/RandomizedQueue.h
	$(CXX) $(CXXFLAGS) -c randomized_queue_test.cpp

../src/RandomizedQueue.o: ../src/RandomizedQueue.c ../src/RandomizedQueue.h
	$(CC) $(CFLAGS) -c ../src/RandomizedQueue.c -o ../src/RandomizedQueue.o

clean:
	rm -f $(TEST_TARGET) $(TEST_OBJS) ../src/RandomizedQueue.o



