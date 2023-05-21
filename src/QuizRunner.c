#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <quiz.h>


int main() {
	int count = 1;
	while(count == 1){
		mainMenu();
		printf("\n Do you want to go back to main menu?\n 1. Yes\n 2. Exit game\n Enter: ");
		scanf("%d", &count);
		printf("\8n");
	}
    return 0;
}