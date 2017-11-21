# MAKEFILE - CMPE 142: The Sleeping TA
CC = g++
EXENAME = exe
MAIN_CPP = main.cpp
SRC_DIR = src

# Make Rules
# make main: Default
main:
	$(CC) ./$(SRC_DIR)/* -o $(EXENAME) -pthread

# make cpp11: Make using c++ 11
cpp11:
	$(CC) -std=c++11 ./$(SRC_DIR)/* -o $(EXENAME) -pthread

# make asm: Start C/C++ compilation but stop before assembling
asm:
	$(CC) -S ./$(SRC_DIR)/*.cpp

# make asmless: Remove files generated from "make asm"
asmless:
	rm ./*.s

# make clean: Remove the executable (if it was generated)
clean:
	rm ./$(EXENAME)