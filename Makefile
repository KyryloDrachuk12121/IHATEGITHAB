CXX = g++
CXXFLAGS = -Wall -std=c++17
SOURCES = main.cpp dynamic_2d_array.cpp
HEADERS = Header1.h
TARGET = ConsoleApplication2

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	del $(TARGET).exe
