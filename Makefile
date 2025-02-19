# Makefile for QuickUnion unit tests
CXX = g++
CXXFLAGS = -std=c++20 -Wall -g -I/usr/include/gtest

# Google Test libraries
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Source and test files
SRC = lecture_1_tests.cpp
TARGET = lecture_1_test

# Build rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(GTEST_LIBS)

# Clean rule
clean:
	rm -f $(TARGET) *.o
