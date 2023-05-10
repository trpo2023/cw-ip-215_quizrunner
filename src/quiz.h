#ifndef QUIZ_H
#define QUIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char question[256];
    char options[4][256];
    int correctOption;
} Question;

int loadQuestions(const char *filename, Question *questions, int numQuestions);
void playQuiz(const char *filename);

#endif
