TARGET = QuizGame
CC = gcc

PREF_SRC = ./src/
PREF_OBJ = ./obj/
PREF_INC = ./src/

SRC = $(wildcard $(PREF_SRC)*.c)
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $^ -o $@

$(PREF_OBJ)%.o : $(PREF_SRC)%.c
	$(CC) -c $< -o $@ -I$(PREF_INC)

$(PREF_OBJ)%.o : $(PREF_SRC)%.c $(PREF_INC)%.h
	$(CC) -c $<%.c -o $@%.o -I$(PREF_INC)

clean:
	rm -f $(TARGET) $(PREF_OBJ)*.o
