cmake_minimum_required(VERSION 3.12)
project(QuizGame)

set(CMAKE_C_STANDARD 11)

# Определение исходных файлов проекта
set(PROJECT_SOURCES
    src/project/QuizRunner.c
    src/project_lib/quiz.c
)

# Определение исходных файлов тестов
set(TEST_SOURCES
    test/tests/test.c
    src/project_lib/quiz.c
)

# Компиляция исполняемого файла вашего проекта
add_executable(QuizGame ${PROJECT_SOURCES})

# Компиляция исполняемого файла тестов
add_executable(Test ${TEST_SOURCES})

# Указание директории с заголовочными файлами
target_include_directories(QuizGame PUBLIC src/project_lib)
target_include_directories(Test PUBLIC src/project_lib)

# Линковка вашего проекта с библиотекой CUnit
target_link_libraries(Test cunit)

# Указание директории с заголовочными файлами CUnit
target_include_directories(Test PUBLIC /usr/include/CUnit)
