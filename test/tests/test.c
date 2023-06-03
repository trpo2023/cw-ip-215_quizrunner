#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "quiz.h"

void test_loadQuestions() {
    // Создаем массив структур Question для хранения загруженных вопросов
    Question questions[10];

    // Предположим, что файл с вопросами называется "topic1.txt"
    const char* filename = "files/topic1.txt";

    // Загружаем вопросы из файла
    int numQuestions = loadQuestions(filename, questions, 10);

    // Проверяем, что количество загруженных вопросов соответствует ожидаемому значению
    CU_ASSERT_EQUAL(numQuestions, 10);

    // Проверяем, что первый вопрос и его данные были корректно загружены
    CU_ASSERT_STRING_EQUAL(questions[0].question, "Solve (2+2)*2-вопрос");
    CU_ASSERT_STRING_EQUAL(questions[0].options[0], "A) 2");
    CU_ASSERT_STRING_EQUAL(questions[0].options[1], "B) 6");
    CU_ASSERT_STRING_EQUAL(questions[0].options[2], "C) 8");
    CU_ASSERT_EQUAL(questions[0].correctOption, 3);
}

int main() {
    // Инициализация библиотеки CUnit
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Создание нового тестового набора
    CU_pSuite suite = CU_add_suite("Quiz Tests", NULL, NULL);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Добавление тестовой функции в набор
    if (CU_add_test(suite, "Test loadQuestions", test_loadQuestions) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Запуск тестов
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
