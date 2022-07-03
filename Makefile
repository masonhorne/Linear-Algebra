# Compilation directives
CC=c++
STD=-std=c++11

# Directories to build/test from
TEST=./test/
BIN=./bin/
SOURCE=./src/

# Target to build
all: execute
execute: matrixtests
	./bin/matrixtests

# Dependency chain for matrixtests
matrixtests: matrixtests.o matrix.o util.o
	$(CC) $(BIN)matrixtests.o $(BIN)matrix.o $(BIN)util.o -o $(BIN)matrixtests
matrixtests.o: matrix.o $(TEST)matrixtests.cpp
	$(CC) $(STD) -c $(BIN)matrix.o $(TEST)matrixtests.cpp -o $(BIN)matrixtests.o
matrix.o: $(SOURCE)matrix.cpp $(SOURCE)matrix.hpp util.o
	$(CC) $(STD) -c $(SOURCE)matrix.cpp $(BIN)util.o -o $(BIN)matrix.o
util.o: $(SOURCE)util.cpp $(SOURCE)util.hpp clean
	$(CC) $(STD) -c $(SOURCE)util.cpp -o $(BIN)util.o

# Clean to remove old executables and create bin directory
clean:
	rm -rf $(BIN)
	mkdir $(BIN)
