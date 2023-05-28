#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "quiz.h"

void test_calculate_score(void) {
    // Создаем структуру Quiz
    Quiz quiz;
    quiz.questions_count = 3;
    quiz.questions = (Question*)malloc(sizeof(Question) * quiz.questions_count);

    // Задаем вопросы и ответы
    quiz.questions[0].question = "2 + 2 * 2 =";
    quiz.questions[0].answers_count = 4;
    quiz.questions[0].answers = (char**)malloc(sizeof(char*) * quiz.questions[0].answers_count);
    quiz.questions[0].answers[0] = "6";
    quiz.questions[0].answers[1] = "8";
    quiz.questions[0].answers[2] = "12";
    quiz.questions[0].answers[3] = "4";
    quiz.questions[0].correct_answer = 1;

    quiz.questions[1].question = "Square root of 144 is";
    quiz.questions[1].answers_count = 4;
    quiz.questions[1].answers = (char**)malloc(sizeof(char*) * quiz.questions[1].answers_count);
    quiz.questions[1].answers[0] = "11";
    quiz.questions[1].answers[1] = "12";
    quiz.questions[1].answers[2] = "9";
    quiz.questions[1].answers[3] = "16";
    quiz.questions[1].correct_answer = 1;

    quiz.questions[2].question = "The factorial of 6 is";
    quiz.questions[2].answers_count = 4;
    quiz.questions[2].answers = (char**)malloc(sizeof(char*) * quiz.questions[2].answers_count);
    quiz.questions[2].answers[0] = "120";
    quiz.questions[2].answers[1] = "650";
    quiz.questions[2].answers[2] = "480";
    quiz.questions[2].answers[3] = "720";
    quiz.questions[2].correct_answer = 3;

    // Вызываем функцию calculate_score и проверяем результат
    int score = calculate_score(&quiz);
    CU_ASSERT_EQUAL(score, 0);

    // Освобождаем память
    free(quiz.questions[0].answers);
    free(quiz.questions[1].answers);
    free(quiz.questions[2].answers);
    free(quiz.questions);
}

void test_load_questions_from_file(void) {
    // Создаем структуру Quiz
    Quiz quiz;
    quiz.questions_count = 0;
    quiz.questions = NULL;

    // Загружаем вопросы из файла
    load_questions_from_file(&quiz, "files/topic1.txt");

    // Проверяем, что вопросы успешно загружены
    CU_ASSERT_EQUAL(quiz.questions_count, 6);
    CU_ASSERT_PTR_NOT_NULL(quiz.questions);

    // Проверяем содержимое первого вопроса
    CU_ASSERT_STRING_EQUAL(quiz.questions[0].question, "Solve (2+2)*2");
    CU_ASSERT_EQUAL(quiz.questions[0].answers_count, 4);
    CU_ASSERT_PTR_NOT_NULL(quiz.questions[0].answers);
    CU_ASSERT_STRING_EQUAL(quiz.questions[0].answers[0], "6");
    CU_ASSERT_STRING_EQUAL(quiz.questions[0].answers[1], "8");
    CU_ASSERT_STRING_EQUAL(quiz.questions[0].answers[2], "12");
    CU_ASSERT_STRING_EQUAL(quiz.questions[0].answers[3], "4");
    CU_ASSERT_EQUAL(quiz.questions[0].correct_answer, 1);

    // Освобождаем память
    for (int i = 0; i < quiz.questions_count; i++) {
        free(quiz.questions[i].answers);
    }
    free(quiz.questions);
}

int main() {
    // Инициализация CUnit
    CU_initialize_registry();

    // Создание тестовой сьюты
    CU_pSuite suite = CU_add_suite("Quiz2 Tests", NULL, NULL);

    // Добавление тестов в сьюту
    CU_add_test(suite, "Test calculate_score", test_calculate_score);
    CU_add_test(suite, "Test load_questions_from_file", test_load_questions_from_file);

    // Запуск всех тестов
    CU_basic_run_tests();

    // Очистка ресурсов CUnit
    CU_cleanup_registry();

    return 0;
}