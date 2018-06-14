CC := g++
CPPFLAGS := -g -Wall -Werror -std=c++11 -I src -I tests/third_party
SRC_DIR := src
OBJ_DIR := obj
TEST_DIR := tests
SRC := $(wildcard $(SRC_DIR)/*.cpp) 
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC)) 

$(TEST_DIR)/debug/runTests: $(OBJ) $(TEST_DIR)/bin/tests_main.o $(TEST_DIR)/bin/linkedListTest.o
	$(CC) $(OBJ) $(TEST_DIR)/bin/tests_main.o $(TEST_DIR)/bin/linkedListTest.o -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

$(TEST_DIR)/bin/tests_main.o: $(TEST_DIR)/tests_main.cpp $(TEST_DIR)/third_party/catch.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<  

$(TEST_DIR)/bin/linkedListTest.o: $(TEST_DIR)/linkedListTest.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

.PHONEY: clean

clean:
	rm $(OBJ_DIR)/*.o 
	rm $(TEST_DIR)/bin/*.o
	rm $(TEST_DIR)/debug/runTests
