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

        // Last line is the correct option
        fgets(line, sizeof(line), file);
        questions[questionIndex].correctOption = atoi(line);

        questionIndex++;
        if (questionIndex >= numQuestions) {
            break;
        }
    }

    fclose(file);
    return 1;
}

void playQuiz(const char *filename) {
    const int numQuestions = 10;
    Question questions[numQuestions];
    int score = 0;

    if (!loadQuestions(filename, questions, numQuestions)) {
        return;
    }

    for (int i = 0; i < numQuestions; i++) {
        printf("Question %d: %s\n", i + 1, questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, questions[i].options[j]);
        }

        int userChoice;
        printf("Select an answer (1-4): ");
        scanf("%d", &userChoice);

        if (userChoice == questions[i].correctOption) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Incorrect. Correct answer: %d\n", questions[i].correctOption);
        }

        printf("\n");
    }

    printf("You scored %d out of %d possible points.\n", score, numQuestions);
}
