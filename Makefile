# Compilation directives
CC=c++
STD=-std=c++11

# Directories to build/test from
TEST=./test/
BIN=./bin/
LOG=./log/
SOURCE=./src/

# Target to build
all: execute
execute: matrixtests
	./bin/matrixtests

# Dependency chain for matrixtests
matrixtests: matrixtests.o matrix.o util.o logger.o iohandler.o
	$(CC) $(BIN)matrixtests.o $(BIN)matrix.o $(BIN)util.o $(BIN)logger.o $(BIN)iohandler.o -o $(BIN)matrixtests
matrixtests.o: matrix.o $(TEST)matrixtests.cpp
	$(CC) $(STD) -c $(BIN)matrix.o $(TEST)matrixtests.cpp -o $(BIN)matrixtests.o
matrix.o: $(SOURCE)matrix.cpp $(SOURCE)matrix.hpp util.o logger.o iohandler.o
	$(CC) $(STD) -c $(SOURCE)matrix.cpp $(BIN)util.o $(BIN)logger.o $(BIN)iohandler.o -o $(BIN)matrix.o
iohandler.o: $(SOURCE)iohandler.cpp $(SOURCE)iohandler.hpp util.o logger.o
	$(CC) $(STD) -c $(SOURCE)iohandler.cpp $(BIN)util.o $(BIN)logger.o -o $(BIN)iohandler.o
logger.o: $(SOURCE)logger.cpp $(SOURCE)logger.hpp
	$(CC) $(STD) -c $(SOURCE)logger.cpp -o $(BIN)logger.o
util.o: $(SOURCE)util.cpp $(SOURCE)util.hpp clean
	$(CC) $(STD) -c $(SOURCE)util.cpp -o $(BIN)util.o

# Clean to remove old executables and create bin directory
clean:
	rm -rf $(BIN)
	rm -rf $(LOG)
	mkdir $(LOG)
	mkdir $(BIN)
