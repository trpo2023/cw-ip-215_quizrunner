#include <quiz.h>

int loadQuestions(const char* filename, Question* questions, int numQuestions) {
    FILE* file = fopen(filename, "r");
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

void playQuiz(const char* filename) {
    const int numQuestions = 10;
    Question questions[numQuestions];
    int score = 0;
    int totalScore = 0;

    if (!loadQuestions(filename, questions, numQuestions)) {
        return;
    }

    for (int i = 0; i < numQuestions; i++) {
        printf("Question %d (Points: %d): %s\n", i + 1, questions[i].score,
               questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, questions[i].options[j]);
        }

        int userChoice;
        printf("Select an answer (1-4): ");
        scanf("%d", &userChoice);

        if (userChoice == questions[i].correctOption) {
            printf("Correct!\n");
            score += questions[i].score;
        } else {
            printf("Incorrect. Correct answer: %d\n",
                   questions[i].correctOption);
        }

        printf("\n");
        totalScore += questions[i].score;
    }

    printf("You scored %d out of %d possible points.\n", score, totalScore);
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

    printf("Creating a new quiz. Please enter the details:\n");

    for (int i = 0; i < 10; i++) {
        printf("Question %d: ", i + 1);
        fgets(question, sizeof(question), stdin);
        fprintf(file, "%s", question);

        for (int j = 0; j < 4; j++) {
            printf("Option %d: ", j + 1);
            fgets(options[j], sizeof(options[j]), stdin);
            fprintf(file, "%s", options[j]);
        }

        printf("Correct option (1-4): ");
        scanf("%d", &correctOption);
        getchar(); // Consume the newline character
        fprintf(file, "%d\n", correctOption);

        printf("Score for the question: ");
        scanf("%d", &score);
        getchar(); // Consume the newline character
        fprintf(file, "%d\n", score);

        printf("\n");
    }

    fclose(file);
    printf("quiz created successfully in file: %s\n", filename);
}

void editTest(const char* filename) {
    FILE* file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Failed to open test file: %s\n", filename);
        return;
    }

    char line[256];
    int questionIndex = 0;
    int blockIndex = 0;

    while (fgets(line, sizeof(line), file)) {
        // Remove the newline character
        line[strcspn(line, "\n")] = '\0';

        if (blockIndex % 7 == 0) {
            printf("Question %d: %s\n", questionIndex + 1, line);
            printf("Enter new question (or 'pass' to skip): ");
            fgets(line, sizeof(line), stdin);
            line[strcspn(line, "\n")] = '\0'; // Remove newline character

            if (strcmp(line, "pass") != 0) {
                fseek(file, -strlen(line) - 1,
                      SEEK_CUR); // Move file pointer back to the start of the
                                 // question line
                fprintf(file, "%s\n", line); // Write new question
            }
        } else {
            printf("Option or answer or score: %s\n", line);
            printf("Enter new option: ");
            fgets(line, sizeof(line), stdin);
            line[strcspn(line, "\n")] = '\0'; // Remove newline character

            fseek(file, -strlen(line) - 1,
                  SEEK_CUR); // Move file pointer back to the start of the
                             // option line
            fprintf(file, "%s\n", line); // Write new option
        }

        blockIndex++;
        if (blockIndex % 7 == 0) {
            printf("\n");
            questionIndex++;
        }
    }

    fclose(file);
    printf("Test edited successfully in file: %s\n", filename);
}

int mainMenu() {
    int choice;
    printf("Greetings! Welcome to QuizRunner ver.4.2.4 by DiSeDgE, Farbez & "
           "Haki. Good luck! \n Choose an option:\n");
    printf("1. Play quiz \n");
    printf("2. Create quiz\n");
    printf("3. Edit quiz\n");
    printf("0. Exit game\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 3) {
        int themenum;
        // char topicnum[256];
        printf("Choose a quiz to edit:\n");
        printf("1. Math\n");
        printf("2. Geometry\n");
        printf("3. Games\n");
        printf("4. My Quiz\n");
        printf("0. Exit game\n");
        printf("Enter the quiz number: ");
        scanf("%d", &themenum);
        getchar();

        if (themenum == 1) {
            editTest("files/topic1.txt");
        } else if (themenum == 2) {
            editTest("files/topic2.txt");
        } else if (themenum == 3) {
            editTest("files/topic3.txt");
        } else if (themenum == 4) {
            editTest("files/my_quiz.txt");
        } else if (themenum == 0) {
            return 0;
        } else {
            printf("Invalid quiz number!\n");
        }
    } else if (choice == 1) {
        int themenum;
        // char topicnum[256];
        printf("Choose a quiz to play:\n");
        printf("1. Math\n");
        printf("2. Geometry\n");
        printf("3. Games\n");
        printf("4. My Quiz\n");
        printf("0. Exit game\n");
        printf("Enter the quiz number: ");
        scanf("%d", &themenum);

        if (themenum == 1) {
            playQuiz("files/topic1.txt");
        } else if (themenum == 2) {
            playQuiz("files/topic2.txt");
        } else if (themenum == 3) {
            playQuiz("files/topic3.txt");
        } else if (themenum == 4) {
            playQuiz("files/my_quiz.txt");
        } else if (themenum == 0) {
            return 0;
        } else {
            printf("Invalid quiz number!\n");
        }
    } else if (choice == 2) {
        createTest("files/my_quiz.txt");
    } else if (choice == 0) {
        return 0;
    } else {
        printf("Invalid choice!\n");
    }
}
