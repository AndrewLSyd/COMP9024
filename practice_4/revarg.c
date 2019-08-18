// revarg.c: reverse the chars in the first command-line argument
#include <stdio.h>
#include <stdlib.h>
#include "quack.h"

int main(int argc, char *argv[]) {
	Quack t = NULL;

	if (argc >= 2) {
		char *inputc = argv[1];
		t = createQuack();
		while (*inputc != '\0') {
			qush(*inputc++, t);
		}
		puts("time to pop!\n");
		while (!isEmptyQuack(t)) {			
			printf("%c", pop(t));
		}
		putchar('\n');
	}
	else {
	fprintf(stderr, "Usage: ./revargLL string");
	return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
