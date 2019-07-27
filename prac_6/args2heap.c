// args2heap.c

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define USAGE_ERROR "Usage: integers...\n"

void check_inp(char * inp){
	// argument: character pointer in a string
	// exits if not all digits
	char * x = inp;
	while (*x){	
		if (! isdigit(*x)){
			fprintf(stderr, USAGE_ERROR);
			exit(EXIT_FAILURE);		
		}
		x ++;
	}	 
}


void print_array(int * x, int n){
	// argument: int pointer, number of elements
	// prints
	for (int * y = x; y < x + n; y ++){
		printf("%d ", *y);
	}
	putchar('\n');
}


void fixUp(int *heap, int child) {
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
	
	int * heap_ptr;	
	heap_ptr = malloc(argc * sizeof(int));
	
	// setting first element to -999
	*heap_ptr = -999;
	
	for (int i=1; i < argc; i ++){
		printf("reading in %s...\n", *(argv + i));
		check_inp(*(argv + i));
		
		// read into last position
		sscanf(*(argv + i), "%d", (heap_ptr + i));
		
		fixUp(heap_ptr, i);
		
	}
	
	// checking read in array
	puts("out array is:\n");;
	print_array(heap_ptr, argc);
	
	// freeing memory and clearing dangling pointers
	free(heap_ptr);
	heap_ptr = NULL;

	return EXIT_SUCCESS;
}
