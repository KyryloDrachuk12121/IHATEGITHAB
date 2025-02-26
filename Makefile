CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -O2 -g -fPIC -I./lib
LDFLAGS = -L./lib -lstatistical_measures -lm
SRC_DIR = .
LIB_DIR = ./lib

PERCOLATION_STATIC = $(LIB_DIR)/libpercolation.a
PERCOLATION_DYNAMIC = $(LIB_DIR)/libpercolation.so
PERCOLATION_SIM_OBJ = $(LIB_DIR)/percolation_simulation.o
DYNAMIC_CONNECTIVITY_OBJ = $(LIB_DIR)/dynamic_connectivity.o
PERCOLATION_OBJ = $(LIB_DIR)/percolation.o
STAT_MEASURES_LIB = -lstatistical_measures

all: percolation_simulation

$(PERCOLATION_STATIC): $(PERCOLATION_OBJ) $(DYNAMIC_CONNECTIVITY_OBJ)
	mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(PERCOLATION_DYNAMIC): $(PERCOLATION_OBJ) $(DYNAMIC_CONNECTIVITY_OBJ)
	mkdir -p $(LIB_DIR)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

$(DYNAMIC_CONNECTIVITY_OBJ): $(SRC_DIR)/dynamic_connectivity.c
	mkdir -p $(LIB_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(PERCOLATION_OBJ): $(SRC_DIR)/percolation.c
	mkdir -p $(LIB_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(PERCOLATION_SIM_OBJ): $(SRC_DIR)/percolation_simulation.c
	mkdir -p $(LIB_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(LIB_DIR)/statistical_measures.o: $(SRC_DIR)/statistical_measures.c
	$(CC) $(CFLAGS) -c $< -o $@
$(LIB_DIR)/libstatistical_measures.a: $(LIB_DIR)/statistical_measures.o
	ar rcs $@ $^
$(LIB_DIR)/libstatistical_measures.so: $(LIB_DIR)/statistical_measures.o
	$(CC) -shared -o $@ $^
percolation_simulation: $(PERCOLATION_SIM_OBJ) $(PERCOLATION_STATIC)
	$(CC) $(CFLAGS) -o percolation_simulation $^ -L$(LIB_DIR) -lpercolation $(STAT_MEASURES_LIB) -lm

clean:
	rm -rf $(LIB_DIR) percolation_simulation















