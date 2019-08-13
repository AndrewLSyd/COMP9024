// prefixes
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv){
	if (argc != 2){
		fprintf(stderr, "Usage: \\.prefixes word");
		return EXIT_FAILURE;
	}
	// Step 1: get the length of the word
	int length=0;
	char * char_pointer = *(argv + 1);
	while (*char_pointer){
		length++;
		char_pointer++;
	}
	printf("length is %d\n", length);
	// Step 2: loop through
	for (int i = length; i>= 0; i--){
		for (int j = 0; j < i; j++){
			printf("%c", *(*(argv + 1) + j));
		}
		puts("\n");
	}
}
