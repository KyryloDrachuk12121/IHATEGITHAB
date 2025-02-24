CC = gcc
CXX = g++

CFLAGS = -Wall -Wextra -g -I../src -I/mnt/c/Users/ruvik/Downloads/dynamic_connectivity/src
CXXFLAGS = -std=c++20 -Wall -Wextra -g -I/usr/include/gtest -I../src -I/mnt/c/Users/ruvik/Downloads/dynamic_connectivity/src

GTEST_LIBS = -lgtest -lgtest_main -pthread

PERCOLATION_SRC = ../src
DYNAMIC_CONNECTIVITY_SRC = /mnt/c/Users/ruvik/Downloads/dynamic_connectivity/src
TEST_SRC = percolation_tests.cpp

run_tests:
	$(CXX) $(CXXFLAGS) $(PERCOLATION_SRC)/percolation.c $(DYNAMIC_CONNECTIVITY_SRC)/dynamic_connectivity.c $(TEST_SRC) $(GTEST_LIBS) -o /dev/shm/percolation_tests && /dev/shm/percolation_tests; rm -f /dev/shm/percolation_tests

valgrind_tests:
	$(CXX) $(CXXFLAGS) $(PERCOLATION_SRC)/percolation.c $(DYNAMIC_CONNECTIVITY_SRC)/dynamic_connectivity.c $(TEST_SRC) $(GTEST_LIBS) -o /dev/shm/percolation_tests && valgrind --leak-check=full /dev/shm/percolation_tests; rm -f /dev/shm/percolation_tests














