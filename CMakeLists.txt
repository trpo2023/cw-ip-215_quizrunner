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
)

# Определение исходных файлов тестов
set(TEST_SOURCES
    test/tests/test.c
    src/project_lib/quiz.c  # Добавлен файл quiz.c
)

# Компиляция исполняемого файла вашего проекта
add_executable(QuizGame ${PROJECT_SOURCES})

# Компиляция исполняемого файла тестов
add_executable(Test ${TEST_SOURCES})

# Подключение библиотеки CUnit
find_library(CUNIT_LIBRARY cunit)

# Линковка вашего проекта с библиотекой CUnit
target_link_libraries(Test ${CUNIT_LIBRARY})

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

# Указание директории с заголовочными файлами
target_include_directories(QuizGame PUBLIC src/project_lib)
target_include_directories(Test PUBLIC src/project_lib)
