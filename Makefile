CC := g++
CPPFLAGS := -g -Wall -Werror -std=c++11 -I src -I tests/third_party
SRC_DIR := src
TEST_DIR := tests
OBJ_DIR := $(TEST_DIR)/bin
SRC := $(wildcard $(SRC_DIR)/*.cpp) 
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC)) 

$(TEST_DIR)/debug/run_tests: $(OBJ) $(OBJ_DIR)/tests_main.o $(OBJ_DIR)/linkedListTest.o
	$(CC) $(OBJ) $(TEST_DIR)/bin/tests_main.o $(TEST_DIR)/bin/linkedListTest.o -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/tests_main.o: $(TEST_DIR)/tests_main.cpp $(TEST_DIR)/third_party/catch.hpp
	$(CC) $(CPPFLAGS) -c -o $@ $<  

$(OBJ_DIR)/linkedListTest.o: $(TEST_DIR)/linear_list_test.cpp
	$(CC) $(CPPFLAGS) -c -o $@ $<

.PHONEY: clean

clean:
	rm $(OBJ_DIR)/*.o 
	rm $(TEST_DIR)/debug/runTests
