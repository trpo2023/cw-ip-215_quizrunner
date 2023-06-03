#include <quiz.h>
#include <stdio.h>


int main()
{
    int count = 1;
    while (count == 1) {
        mainMenu();
        printf("\n Do you want to go back to main menu?\n 1. Yes\n 2. Exit "
               "game\n "
               "Enter: ");
        scanf("%d", &count);
        printf("\n\n\n\n\n\n\n\n");
    }
    return 0;
}