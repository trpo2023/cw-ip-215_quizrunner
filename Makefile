TARGET = QuizGame
TEST_TARGER = Test
CC = gcc

PREF_SRC = ./src/
PREF_OBJ = ./obj/
PREF_INC = ./src/
PREF_TEST = ./test-files/
PREF_TEST_INC = ./test-files/

SRC = $(wildcard $(PREF_SRC)*.c)
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))
TEST_SRC = $(wildcard $(PREF_TEST)*.c) 
TEST_OBJ = $(patsubst $(PREF_TEST)%.c, $(PREF_OBJ)%.o, $(TEST_SRC))

$(TARGET) : $(OBJ)
	$(CC) $^ -o $@

$(PREF_OBJ)%.o : $(PREF_SRC)%.c
	$(CC) -c $< -o $@ -I$(PREF_INC)

$(PREF_OBJ)%.o : $(PREF_SRC)%.c $(PREF_INC)%.h
	$(CC) -c $<%.c -o $@%.o -I$(PREF_INC)


$(PREF_OBJ)test_%.o: $(PREF_TEST)test_%.c 
	$(CC) -c $< -o $@ -I$(PREF_TEST_INC)

test: $(OBJ) $(TEST_OBJ) 
	$(CC) $^ -o $@

clean:
	rm -f $(TARGET) $(PREF_OBJ)*.o
