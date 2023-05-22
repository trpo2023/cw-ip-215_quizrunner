#ifndef QUIZ_H
#define QUIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char question[256];
    char options[4][256];
    int correctOption;
    int score;
} Question;

int loadQuestions(const char *filename, Question *questions, int numQuestions);
void playQuiz(const char *filename);
void createTest(const char *filename);
void editTest(const char *filename);
int mainMenu();

#endif
