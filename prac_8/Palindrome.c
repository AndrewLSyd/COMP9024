// psuedocode for palindrome detector
// could use a stack and pop off it to reverse it
// or could just reverse it using a for loop and do a string comp


// complexity... linear

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char ** argv){
	puts("running palindrome...\n");
	printf("number of inputs is %d\n", argc - 1);
	if (argc - 1 != 1){
		return EXIT_FAILURE;
	}
	printf("input is %s\n", *(argv + 1));  // dereference once to get to series of pointers
	int length = strlen(*(argv + 1));
	printf("length of string is %d\n", length);
	
	// constant time
	char * str_rev = NULL;
	str_rev = malloc((length + 1) * sizeof(char));
	if (str_rev == NULL){
		fprintf(stderr, "MEMORY ERROR");
		EXIT_FAILURE;
	}
	
	// linear time
	for (int i=0; i < length; i++){
		char temp_char;
		temp_char = *(*(argv + 1) + length -1 - i);
		printf("\t%d: %c\n", i, temp_char);
		*(str_rev + i) = temp_char;
	}
	*(str_rev + length) = '\0';
	
	printf("reverse char is %s\n", str_rev);
	
	// linear time
	if (strcmp(*(argv + 1), str_rev) == 0){
		puts("SUCCESS! PALINDROME\n");
	}
	else {
		puts("FAILURE! NOT A PALINDROME\n");	
	}
	
	// cleanup
	free(str_rev);
	str_rev = NULL;	
	
	return EXIT_SUCCESS;
}
