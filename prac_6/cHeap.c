// args2heap.c

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define USAGE_ERROR "Usage: single alphanumeric inputs...\n"

void print_array(char * x, int n){
	// argument: int pointer, number of elements
	// prints
	for (char * y = x; y < x + n; y ++){
		printf("%c ", *y);
	}
	putchar('\n');
}


void check_inp(char * inp){
	// argument: character pointer in a string
	// exits if not all alphanumeric
	char * x = inp;
	int counter = 0;
	
	while (*x){	
		if (!(*x >= 48 && *x <= 122)){
			fprintf(stderr, USAGE_ERROR);
			exit(EXIT_FAILURE);		
		}
		if ((*x >= 58 && *x <= 64) || (*x >= 94 && *x <= 96)){
			fprintf(stderr, USAGE_ERROR);
			exit(EXIT_FAILURE);		
		}
		x ++;
		counter ++;	
	}
	
	if (counter != 1){
		fprintf(stderr, USAGE_ERROR);
		exit(EXIT_FAILURE);	
	}
}


void fixUp(char *heap, int child) {
   while (child>1 && heap[child/2]<heap[child]) {
      int swap = heap[child];         // if parent < child, do a swap
      heap[child] = heap[child/2];
      heap[child/2] = swap;
      child = child/2;                // become the parent
   }
   return;
}


int main(int argc, char ** argv){
	//int in;
	
	if (argc == 1){
		fprintf(stderr, USAGE_ERROR);
		return EXIT_FAILURE;
	}
	
	char * heap_ptr;	
	heap_ptr = malloc((argc - 1) * sizeof(char));
	
	// setting first element to -999
	*heap_ptr = ' ';
	
	for (int i=1; i < argc; i ++){
		printf("reading in %s...\n", *(argv + i));
		check_inp(*(argv + i));
		
		// read into last position
		sscanf(*(argv + i), "%c", (heap_ptr + i));
		
		fixUp(heap_ptr, i);
		
	}
	
	puts("out array is:\n");;
	print_array(heap_ptr, argc);
	
	// freeing memory and clearing dangling pointers
	free(heap_ptr);
	heap_ptr = NULL;

	return EXIT_SUCCESS;
}
