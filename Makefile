TARGET = QuizGame
CC = gcc
TEST_TARGET = Test

SRS_DIR = ./src/project/
SRS_DIR2 = ./src/project_lib/
OBJ_DIR = ./obj/src/project_lib/
PREF_INC = ./src/project_lib/
TEST_DIR = ./test-file/test_lib/
TEST_DIR2 = ./test-file/test_project/
TEST_OBJ_DIR = ./obj/test_src/test_lib/
PREF_TEST_INC = ./test-file/test_lib/

SRC = $(wildcard $(SRS_DIR)*.c) $(wildcard $(SRS_DIR2)*.c)
OBJ = $(patsubst $(SRS_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
TEST_SRC = $(wildcard $(TEST_DIR)*.c) $(wildcard $(TEST_DIR2)*.c)
TEST_OBJ = $(patsubst $(TEST_DIR)%.c, $(TEST_OBJ_DIR)%.o, $(TEST_SRC))

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ -I$(PREF_INC)

$(OBJ_DIR)%.o: $(SRS_DIR)%.c
	$(CC) -c $< -o $@ -I$(PREF_INC)

$(OBJ_DIR)%.o: $(SRS_DIR)%.c $(PREF_INC)%.h
	$(CC) -c $< -o $@ -I$(PREF_INC)

$(TEST_TARGET): $(TEST_OBJ)
	$(CC) $^ -o $@ -I$(PREF_TEST_INC)

$(TEST_OBJ_DIR)%.o: $(TEST_DIR)%.c
	$(CC) -c $< -o $@ -I$(PREF_TEST_INC)

$(TEST_OBJ_DIR)%.o: $(TEST_DIR)%.c $(PREF_TEST_INC)%.h
	$(CC) -c $< -o $@ -I$(PREF_TEST_INC)

.PHONY: test
test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(OBJ_DIR)*.o $(TEST_OBJ_DIR)*.o $(TEST_TARGET)