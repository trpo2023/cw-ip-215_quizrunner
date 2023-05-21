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


void createTest(const char *filename) {
    FILE *file = fopen(filename, "w");
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
        getchar();  // Consume the newline character
        fprintf(file, "%d\n", correctOption);

        printf("Score for the question: ");
        scanf("%d", &score);
        getchar();  // Consume the newline character
        fprintf(file, "%d\n", score);

        printf("\n");
    }

    fclose(file);
    printf("quiz created successfully in file: %s\n", filename);
}


void editTest(const char *filename) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Failed to open quiz file: %s\n", filename);
        return;
    }

    char line[256];
    int questionIndex = 0;

    while (fgets(line, sizeof(line), file)) {
        // Remove the newline character
        line[strcspn(line, "\n")] = '\0';

        // First line is the question
        printf("Question %d: %s\n", questionIndex + 1, line);

        // Next four lines are the answer options
        for (int i = 0; i < 4; i++) {
            fgets(line, sizeof(line), file);
            line[strcspn(line, "\n")] = '\0';
            printf("Option %d: %s\n", i + 1, line);
        }

        // Fifth line is the correct option
        fgets(line, sizeof(line), file);
        line[strcspn(line, "\n")] = '\0';
        printf("Correct option: %s\n", line);

        // Sixth line is the score
        fgets(line, sizeof(line), file);
        line[strcspn(line, "\n")] = '\0';
        printf("Score: %s\n", line);

        printf("\n");

        // Skip newline character from previous input
        getchar();

        printf("Enter new question (or 'pass' to skip): ");
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0'; // Remove newline character

        if (strcmp(line, "pass") != 0) {
            fprintf(file, "%s\n", line); // Add newline character to written line

            for (int i = 0; i < 4; i++) {
                printf("Enter option %d: ", i + 1);
                fgets(line, sizeof(line), stdin);
                line[strcspn(line, "\n")] = '\0';
                fprintf(file, "%s\n", line);
            }

            printf("Enter correct option (1-4): ");
            fgets(line, sizeof(line), stdin);
            line[strcspn(line, "\n")] = '\0';
            fprintf(file, "%s\n", line);

            printf("Enter score: ");
            fgets(line, sizeof(line), stdin);
            line[strcspn(line, "\n")] = '\0';
            fprintf(file, "%s\n", line);
        }

        questionIndex++;
    }

    fclose(file);
    printf("quiz edited successfully in file: %s\n", filename);
}


void mainMenu() {
    int choice;
    printf("Greetings! Welcome to QuizRunner ver.4.2.4 by DiSeDgE, Farbez & Haki. Good luck! \n Choose an option:\n");
    printf("1. Play quiz \n");
    printf("2. Create quiz\n");
    printf("3. Edit quiz\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 3) {
        int themenum;
        char topicnum[256];
        printf("Choose a quiz to edit:\n");
        printf("1. Math\n");
        printf("2. Geometry\n");
        printf("3. Games\n");
        printf("4. My Quiz\n");
        printf("Enter the quiz number: ");
        scanf("%d", &themenum);

        if (themenum == 1) {
            editTest("topic1.txt");
        } else if (themenum == 2) {
            editTest("topic2.txt");
        } else if (themenum == 3) {
            editTest("topic3.txt");
        } else if (themenum == 4) {
            editTest("my_quiz.txt");
        } else {
            printf("Invalid quiz number!\n");
        }
    } else if (choice == 1) {
        int themenum;
        char topicnum[256];
        printf("Choose a quiz to play:\n");
        printf("1. Math\n");
        printf("2. Geometry\n");
        printf("3. Games\n");
        printf("4. My Quiz\n");
        printf("Enter the quiz number: ");
        scanf("%d", &themenum);

        if (themenum == 1) {
            playQuiz("topic1.txt");
        } else if (themenum == 2) {
            playQuiz("topic2.txt");
        } else if (themenum == 3) {
            playQuiz("topic3.txt");
        } else if (themenum == 4) {
            playQuiz("my_quiz.txt");
        } else {
            printf("Invalid quiz number!\n");
        }
    } else if (choice == 2) {
        createTest("my_quiz.txt");
    } else {
        printf("Invalid choice!\n");
    }
}