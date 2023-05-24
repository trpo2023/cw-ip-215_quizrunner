#ifndef CTESTLIB_H
#define CTESTLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int score;
  char question[100];
  char options[4][50];
  int correctOption;
} Question;

int loadQuestions(const char *filename, Question *questions, int numQuestions);
int TestplayQuiz(const char *filename);
void createTest(const char *filename);
int test_createTest();
int test_editTest();

#endif