// base2.c

#include <stdlib.h>
#include <stdio.h>
#include "quack.h"
#include <ctype.h>


int check_valid_input(char * x){
	fputs("checking if the input is a number...\n", stdout);
	while(*x){
		printf("%c", *x);
		if (!isdigit(*x)){
			fprintf(stderr, "\nnot all input are digits!\n");
			exit(EXIT_FAILURE);
		}
		puts("...OK...");
		x ++;
	}	
	fputs("input is a number!\n", stdout);
	return EXIT_SUCCESS;
}

int main(int argc, char ** argv){
	int n, b;
	
	if (argc != 3){
		fprintf(stderr, "Usage: ./base number base\n");
		return EXIT_FAILURE;
	}
	printf("you have entered number %s, base %s.\n", *(argv + 1), *(argv + 2));

	// check if it is valid
	check_valid_input(*(argv + 1));
	check_valid_input(*(argv + 2));

	sscanf(*(argv + 1), "%d", &n);
	b = atoi(*(argv + 2));

	printf("converting number to an integer using sscanf... %d\n", n);
	printf("converting base to an integer using atoi... %d\n", b);
	
	// setting up quack
 	Quack t = NULL;

	t = createQuack();

	fputs("start of loop\n", stdout);
	while (n > 0){
		printf("push %d %% %d ==> %d\n", n, b, n%b);
		if (n%b == 10){
			push('a', t);
		}
		else if (n%b == 11){
			push('b', t);
		}
		else if (n%b == 12){
			push('c', t);
		}
		else if (n%b == 13){
			push('d', t);
		}
		else if (n%b == 14){
			push('e', t);
		}
		else if (n%b == 15){
			push('f', t);
		}
		else if (n%b == 16){
			push('g', t);
		}
		else {
			push(n%b + '0', t);
		}
		showQuack(t);		
		printf("n = %d/%d\n", n, b);
		n = n / b;
	}
	puts("popping...\n");
	while(!isEmptyQuack(t)){
		printf("%c", pop(t));
	}
	puts("\n");
	return EXIT_SUCCESS;
}
