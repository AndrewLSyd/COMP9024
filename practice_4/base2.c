// base2.c

#include <stdlib.h>
#include <stdio.h>
#include "quack.h"
#include <ctype.h>

#define BASE 2

int main(int argc, char ** argv){
	if (argc != 2){
		fprintf(stderr, "Usage: ./base2 number\n");
		return EXIT_FAILURE;
	}
	printf("you have entered %s\n", *(argv + 1));

	// check if it is valid
	puts("checking if all digits...\n");
	char * x = *(argv + 1);
	while(*x){
		printf("%c", *x);
		if (!isdigit(*x)){
			fprintf(stderr, "\nnot all input are digits!\n");
			exit(EXIT_FAILURE);
		}
		puts("..ok..");
		x ++;
	}

	printf("\nconverting this to an integer using atoi... %d\n", atoi(*(argv + 1)));
	int n;
	sscanf(*(argv + 1), "%d", &n);
	printf("converting this to an integer using sscanf... %d\n", n);

	// setting up quack
 	Quack t = NULL;

	t = createQuack();

	fputs("start of loop", stdout);
	while (n > 0){
		printf("push %d %% %d ==> %d\n", n, BASE, n%BASE);
		push(n%BASE, t);
		showQuack(t);		
		printf("n = %d/%d\n", n, BASE);
		n = n / BASE;
	}
	puts("popping...\n");
	while(!isEmptyQuack(t)){
		printf("%d", pop(t));
	}
	puts("\n");
	return EXIT_SUCCESS;
}
