#include "quiz.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdio.h>
#include <string.h>

void test_loadQuestions()
{
    // Create a temporary test file with sample questions
    FILE* testFile = fopen("test_questions.txt", "w");
    if (testFile == NULL) {
        CU_FAIL("Failed to create test file");
        return;
    }

    fprintf(testFile, "Question 1\n");
    fprintf(testFile, "Option 1\n");
    fprintf(testFile, "Option 2\n");
    fprintf(testFile, "Option 3\n");
    fprintf(testFile, "Option 4\n");
    fprintf(testFile, "2\n");
    fprintf(testFile, "10\n");

    fprintf(testFile, "Question 2\n");
    fprintf(testFile, "Option A\n");
    fprintf(testFile, "Option B\n");
    fprintf(testFile, "Option C\n");
    fprintf(testFile, "Option D\n");
    fprintf(testFile, "3\n");
    fprintf(testFile, "5\n");

    fclose(testFile);

    // Test the loadQuestions function
    Question questions[2];
    int result = loadQuestions("test_questions.txt", questions, 2);

    // Assertions using CUnit macros
    CU_ASSERT_EQUAL(result, 1);
    CU_ASSERT_STRING_EQUAL(questions[0].question, "Question 1");
    CU_ASSERT_STRING_EQUAL(questions[0].options[0], "Option 1");
    CU_ASSERT_STRING_EQUAL(questions[0].options[1], "Option 2");
    CU_ASSERT_STRING_EQUAL(questions[0].options[2], "Option 3");
    CU_ASSERT_STRING_EQUAL(questions[0].options[3], "Option 4");
    CU_ASSERT_EQUAL(questions[0].correctOption, 2);
    CU_ASSERT_EQUAL(questions[0].score, 10);

    CU_ASSERT_STRING_EQUAL(questions[1].question, "Question 2");
    CU_ASSERT_STRING_EQUAL(questions[1].options[0], "Option A");
    CU_ASSERT_STRING_EQUAL(questions[1].options[1], "Option B");
    CU_ASSERT_STRING_EQUAL(questions[1].options[2], "Option C");
    CU_ASSERT_STRING_EQUAL(questions[1].options[3], "Option D");
    CU_ASSERT_EQUAL(questions[1].correctOption, 3);
    CU_ASSERT_EQUAL(questions[1].score, 5);
}

void test_playQuiz()
{
    // Create a temporary test file with sample questions
    FILE* testFile = fopen("test_questions.txt", "w");
    if (testFile == NULL) {
        CU_FAIL("Failed to create test file");
        return;
    }

    fprintf(testFile, "Question 1\n");
    fprintf(testFile, "Option 1\n");
    fprintf(testFile, "Option 2\n");
    fprintf(testFile, "Option 3\n");
    fprintf(testFile, "Option 4\n");
    fprintf(testFile, "2\n");
    fprintf(testFile, "10\n");

    fclose(testFile);

    // Create a temporary test input file
    FILE* inputFile = fopen("test_input.txt", "w");
    if (inputFile == NULL) {
        CU_FAIL("Failed to create test input file");
        return;
    }

    fprintf(inputFile, "1\n"); // Choose option 1 for Question 1

    fclose(inputFile);

    // Redirect input from a file instead of the console
    freopen("test_input.txt", "r", stdin);

    // Capture the output from the playQuiz function
    FILE* outputFile = fopen("test_output.txt", "w");
    if (outputFile == NULL) {
        CU_FAIL("Failed to create test output file");
        return;
    }

    // Redirect output to a file instead of the console
    freopen("test_output.txt", "w", stdout);

    // Test the playQuiz function
    playQuiz("test_questions.txt");

    // Restore input and output
    freopen("/dev/tty", "r", stdin);
    freopen("/dev/tty", "w", stdout);

    // Compare the output with the expected output
    FILE* expectedOutputFile = fopen("expected_output.txt", "r");
    if (expectedOutputFile == NULL) {
        CU_FAIL("Failed to open expected output file");
        return;
    }

    FILE* testOutputFile = fopen("expected_output.txt", "r");
    if (testOutputFile == NULL) {
        CU_FAIL("Failed to open test output file");
        return;
    }

    int c1, c2;
    do {
        c1 = fgetc(expectedOutputFile);
        c2 = fgetc(testOutputFile);
        if (c1 != c2) {
            CU_FAIL("Output does not match expected output");
            break;
        }
    } while (c1 != EOF && c2 != EOF);

    fclose(expectedOutputFile);
    fclose(testOutputFile);

    // Remove temporary files
    remove("test_questions.txt");
    remove("test_input.txt");
    remove("test_output.txt");
    remove("expected_output.txt");

    // Assertion using CUnit macro
    CU_ASSERT_EQUAL(c1, EOF);
}

int main()
{
    // Initialize CUnit test registry
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Create a test suite
    CU_pSuite suite = CU_add_suite("Quiz Tests", NULL, NULL);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the test cases to the suite
    if (CU_add_test(suite, "test_loadQuestions", test_loadQuestions) == NULL
        || CU_add_test(suite, "test_playQuiz", test_playQuiz) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all the tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Cleanup and return
    CU_cleanup_registry();
    return CU_get_error();
}
