#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctestlib.h>

int loadQuestions(const char *filename, Question *questions, int numQuestions) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 0;
    }
    
    char line[256];
    int questionIndex = 0;

    while (fgets(line, sizeof(line), file)) {
        // Remove the newline character
        line[strcspn(line, "\n")] = '\0';

        // First line is the question
        strcpy(questions[questionIndex].question, line);

        // Next four lines are the answer options
        for (int i = 0; i < 4; i++) {
            fgets(line, sizeof(line), file);
            line[strcspn(line, "\n")] = '\0';
            strcpy(questions[questionIndex].options[i], line);
        }

        // Penultimate line is the correct option
        fgets(line, sizeof(line), file);
        questions[questionIndex].correctOption = atoi(line);

        // Last line is the score
        fgets(line, sizeof(line), file);
        questions[questionIndex].score = atoi(line);

        questionIndex++;
        if (questionIndex >= numQuestions) {
            break;
        }
    }

    fclose(file);
    return 1;
}


int TestplayQuiz(const char *filename) {
    const int numQuestions = 10;
    Question questions[numQuestions];
    int score = 0;
    int totalScore = 0;
	int result3 = 0;
	
    if (!loadQuestions(filename, questions, numQuestions)) {
        return 0;
    }

    // Enter test data for quiz
    int userChoices[10] = {2, 2, 4, 1, 1, 4, 4, 3, 3, 3};

    for (int i = 0; i < numQuestions; i++) {
        int userChoice = userChoices[i];

        if (userChoice == questions[i].correctOption) {
            score += questions[i].score;
        }

        totalScore += questions[i].score;
    }

    if (score == totalScore) {
        //printf("test_playQuiz completed!\n");
        return result3 = 1;
    } else {
        //printf("test_playQuiz failed!\n");
        return result3 = 0;
    }
}


void createTest(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to create quiz file: %s\n", filename);
        return;
    }

    char question[256];
    char options[4][256];
    int correctOption;
    int score;

    const char* inputQuestion = "abcdefghklmnoprst";
    const char* inputOptions[] = {
        "asdfgh",
        "qwerty",
        "aboba",
        "omwtym"
    };
    const char* inputCorrectOption = "69";
    const char* inputScore = "420";


    strcpy(question, inputQuestion);
    for (int i = 0; i < 4; i++) {
        strcpy(options[i], inputOptions[i]);
    }
    sscanf(inputCorrectOption, "%d", &correctOption);
    sscanf(inputScore, "%d", &score);


    fprintf(file, "%s\n", question);
    for (int i = 0; i < 4; i++) {
        fprintf(file, "%s\n", options[i]);
    }
    fprintf(file, "%d\n", correctOption);
    fprintf(file, "%d\n", score);

    fclose(file);
    //printf("Quiz created successfully in file: %s\n", filename);
}


int test_createTest() {
    const char* expectedLines[] = {
        "abcdefghklmnoprst",
        "asdfgh",
        "qwerty",
        "aboba",
        "omwtym",
        "69",
        "420"
    };

    createTest("files/testcreate.txt");

    FILE* file = fopen("files/testcreate.txt", "r");
    if (file == NULL) {
        printf("error unable to open files/testcreate.txt\n");
        return 0;
    }

    char line[256];
    int lineIndex = 0;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, expectedLines[lineIndex]) != 0) {
            printf("error: line %d incorrect\n", lineIndex + 1);
            fclose(file);
            return 0;
        }

        lineIndex++;
    }

    fclose(file);

    if (lineIndex != sizeof(expectedLines) / sizeof(expectedLines[0])) {
        printf("error: unexpected lines number\n");
        return 0;
    }

    return 1;
}


int test_editTest() {
    const char* expectedLines[] = {
        "abcdefghklmnoprst",
        "asdfgh",
        "qwerty",
        "aboba",
        "omwtym",
        "69",
        "420"
    };


    FILE* file = fopen("files/testcreate.txt", "r");
    if (file == NULL) {
        return 0;
    }

    char line[256];
    int lineIndex = 0;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, expectedLines[lineIndex]) != 0) {;
            fclose(file);
            return 0;
        }

        lineIndex++;
    }

    fclose(file);

    if (lineIndex != sizeof(expectedLines) / sizeof(expectedLines[0])) {
        printf("error: unexpected lines number\n");
        return 0;
    }

    return 1;
}
