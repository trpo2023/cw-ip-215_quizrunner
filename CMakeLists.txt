cmake_minimum_required(VERSION 3.12)

# Название вашего проекта
project(QuizGame)

# Настройка компилятора и стандарта языка
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_C_STANDARD 11)

# Определение исходных файлов проекта
set(PROJECT_SOURCES
    src/project/QuizRunner.c
    src/project_lib/quiz.c
    src/project_lib/quiz.h
)

# Определение исходных файлов тестов
set(TEST_SOURCES
    test/tests/test.c
)

# Компиляция исполняемого файла вашего проекта
add_executable(QuizGame ${PROJECT_SOURCES})

# Компиляция исполняемого файла тестов
add_executable(Test ${TEST_SOURCES})

# Подключение библиотеки Google Test
add_subdirectory(gtest/googletest-main)
include_directories(gtest/googletest/include)

# Линковка вашего проекта с библиотекой Google Test
target_link_libraries(Test gtest)

# Указание цели сборки проекта и тестов
add_custom_target(build
    COMMAND cmake --build . --target all
    DEPENDS QuizGame Test
)

# Указание цели запуска тестов
add_custom_target(run_tests
    COMMAND ./Test
    DEPENDS Test
)
