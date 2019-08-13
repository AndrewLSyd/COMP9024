//

#include <stdlib.h>
#include <stdio.h>
#include "quack.h"

// char ** argv is a pointer to a pointer (e.g. an array of array of words)
int main(int argc, char ** argv){
	fputs("starting program...\n", stdout);
	char input_char;
	fputs("creating quack...\n", stdout);
	Quack quack = NULL;
	quack = createQuack();
	char temp;
		
	while (scanf("%c", &input_char) == 1){
		if (input_char == '\n'){
			break;
		}		
// 		printf("processing '%c'\n", input_char);
		if(input_char == '(' || input_char == '[' || input_char == '{'){
			printf("open bracket '%c' detected, pushing...\n", input_char);
			push(input_char, quack);
			fputs("\t", stdout);
			showQuack(quack);
		}
		else if(input_char == ')'){
			printf("close bracket '%c' detected, pushing...\n", input_char);
			temp = pop(quack);
			printf("\tcomparing %c with %c", temp, input_char);
			if(temp != '('){
				fprintf(stderr, "Mismatch A: not same then mixed kinds of brackets");
				return EXIT_FAILURE;
			}
			fputs("\t", stdout);
			showQuack(quack);
		}
		else if(input_char == ']'){
			printf("close bracket '%c' detected, pushing...\n", input_char);
			temp = pop(quack);
			printf("\tcomparing %c with %c", temp, input_char);
			if(temp != '['){
				fprintf(stderr, "Mismatch A: not same then mixed kinds of brackets");
				return EXIT_FAILURE;
			}
			fputs("\t", stdout);
			showQuack(quack);
		}
		else if(input_char == '}'){
			printf("close bracket '%c' detected, pushing...\n", input_char);
			temp = pop(quack);
			printf("\tcomparing %c with %c", temp, input_char);
			if(temp != '{'){
				fprintf(stderr, "Mismatch A: not same then mixed kinds of brackets");
				return EXIT_FAILURE;
			}
			fputs("\t", stdout);
			showQuack(quack);
		}
	}
	
	if (!isEmptyQuack(quack)){
		fprintf(stderr, "Mismatch C: missing closing brackets");
		return EXIT_FAILURE;		
	}
	fputs("no unmatched brackets!\n", stdout);
	return EXIT_SUCCESS;
}
