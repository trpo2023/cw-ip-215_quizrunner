#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctestlib.h>

int main() {
    int result1 = test_createTest(), result2 = test_editTest();
	int result3 = TestplayQuiz("files/topictest1.txt");
    if (result1) {
        printf("\ntest_createTest completed!\n");
    } else {
        printf("\ntest_createTest failed!\n");
    }
    if (result2) {
        printf("\ntest_editTest completed!\n");
    } else {
        printf("\ntest_editTest failed!\n");
    }
    if (result3) {
        printf("\ntest_playQuiz completed!\n");
    } else {
        printf("\ntest_playQuiz failed!\n");
    }
	TestplayQuiz("files/topictest1.txt");
	if(result1 + result2 + result3 == 3){
		printf("\nAll tests passed successfully!\n");
		printf("\n######     #     #####   #####\n#     #   # #   #     # #     #\n#     #  #   #  #       #      \n######  #     #  #####   ##### \n#       #######       #       #\n#       #     # #     # #     #\n#       #     #  #####   ##### \n");
	}else{
		printf("\n####### ######  ######  ####### ###### \n#       #     # #     # #     # #     #\n#       #     # #     # #     # #     #\n#####   ######  ######  #     # ###### \n#       #   #   #   #   #     # #   #  \n#       #    #  #    #  #     # #    # \n####### #     # #     # ####### #     #\n");
	}
    return 0;
}
