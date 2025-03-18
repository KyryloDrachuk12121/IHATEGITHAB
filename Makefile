CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c11
CXXFLAGS = -Wall -Wextra -std=c++14
GTEST_LIBS = -lgtest -lgtest_main -pthread
TARGETS = brute fast unit_tests

all: $(TARGETS)

brute: Brute.c point.c
	$(CC) $(CFLAGS) -o brute Brute.c point.c

fast: Fast.c point.c
	$(CC) $(CFLAGS) -o fast Fast.c point.c

unit_tests: tests.cpp point.c
	$(CXX) $(CXXFLAGS) -o unit_tests tests.cpp point.c $(GTEST_LIBS)

run_brute: brute
	./brute input.txt

run_fast: fast
	./fast input.txt

run_tests: unit_tests
	./unit_tests

clean:
	rm -f $(TARGETS)