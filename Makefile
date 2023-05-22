TARGET = QuizGame
CC = gcc
TEST_TARGET = Test

PREF_SRC = ./src/
PREF_OBJ = ./obj/
PREF_INC = ./src/
PREF_TEST = ./test-file/
PREF_TEST_INC = ./test-file/
PREF_OBJ_TEST = ./bin/

SRC = $(wildcard $(PREF_SRC)*.c)
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))
TEST_SRC = $(wildcard $(PREF_TEST)*.c) 
TEST_OBJ = $(patsubst $(PREF_TEST)%.c, $(PREF_OBJ_TEST)%.o, $(TEST_SRC)) 

$(TARGET) : $(OBJ)
	$(CC) $^ -o $@

$(PREF_OBJ)%.o : $(PREF_SRC)%.c
	$(CC) -c $< -o $@ -I$(PREF_INC)

$(PREF_OBJ)%.o : $(PREF_SRC)%.c $(PREF_INC)%.h
	$(CC) -c $<%.c -o $@%.o -I$(PREF_INC)

$(TEST_TARGET) : $(TEST_OBJ)
	$(CC) $^ -o $@

$(PREF_OBJ_TEST)%.o : $(PREF_TEST)%.c
	$(CC) -c $< -o $@ -I$(PREF_TEST_INC)

$(PREF_OBJ_TEST)%.o : $(PREF_TEST)%.c $(PREF_TEST_INC)%.h
	$(CC) -c $<%.c -o $@%.o -I$(PREF_TEST_INC)

.PHONY: test
test: $(TEST_TARGET)
	./Test

clean:
	rm -f $(TARGET) $(PREF_OBJ)*.o $(PREF_OBJ_TEST)*.o $(TEST_TARGET)