// ackermann.c

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>

#define USAGE_ERROR "Usage: number number\n"

void check_inp(char * inp){
	char * x = inp;
	while (*x){	
		if (! isdigit(*x)){
			fprintf(stderr, USAGE_ERROR);
			exit(EXIT_FAILURE);		
		}
		x ++;
	}	 
}

int ackermann(int m, int n){
	printf("m is %d, n is %d\n", m, n);
	
	if (m == 0 && n >= 0){
		return n + 1;
	}	
	
	if (m > 0 && n == 0){
		return ackermann(m - 1, 1);
	}	
	
	return ackermann(m - 1, ackermann(m, n - 1));
}

int main(int argc, char ** argv){
	int num_1 = INT_MIN, num_2 = INT_MIN;

	if (argc != 3){
		fprintf(stderr, USAGE_ERROR);
		return EXIT_FAILURE;
	}
	
	printf("*(argv): %s\n", *(argv ));  // program name
	printf("*(argv + 1): %s\n", *(argv + 1));  // first command line input
	printf("*(argv + 2): %s\n", *(argv + 2));  // second command line input
		
	check_inp(*(argv + 1));
	check_inp(*(argv + 2));
	 
	sscanf(*(argv + 1), "%d", &num_1);
	printf("num_1: %d\n", num_1);
	sscanf(*(argv + 2), "%d", &num_2);
	printf("num_2: %d\n", num_2);

	printf("running ackermann...\n");
	
	printf("final result... %d\n", ackermann(num_1, num_2));
	
	return EXIT_SUCCESS;
}
