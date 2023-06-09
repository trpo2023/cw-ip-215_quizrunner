TARGET = QuizGame
CC = gcc

SRS_DIR = ./src/project/
SRS_DIR2 = ./src/project_lib/
OBJ_DIR = ./obj/src/project_lib/
PREF_INC = ./src/project_lib/

SRC = $(wildcard $(SRS_DIR)*.c) $(wildcard $(SRS_DIR2)*.c)
OBJ = $(patsubst $(SRS_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ -I$(PREF_INC)

$(OBJ_DIR)%.o: $(SRS_DIR)%.c
	$(CC) -c $< -o $@ -I$(PREF_INC)

$(OBJ_DIR)%.o: $(SRS_DIR)%.c $(PREF_INC)%.h
	$(CC) -c $< -o $@ -I$(PREF_INC)

projectfile :=$(shell find . -type f -name '*.c')
libfile := $(shell find . -type f -name '*.h')

.PHONY: test clean format

test:
	sudo apt-get update && sudo apt-get install cmake && sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev
	cd build && cmake .. && make && make Test && ./Test
clean:
	rm -f $(TARGET) $(OBJ_DIR)*.o
	cd build && rm -f expected_output.txt
	cd build && make clean
	rm -r build/*

format:
	clang-format -i $(projectfile) $(libfile)