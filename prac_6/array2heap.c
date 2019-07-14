// array2heap.c

#include <stdlib.h>
#include <stdio.h>

int heap[] = {-999,1,2,3,4,5,6,7};
int N = 8;

void fixUp(int *heap, int child) {
   while (child>1 && heap[child/2]<heap[child]) {
      int swap = heap[child];         // if parent < child, do a swap
      heap[child] = heap[child/2];
      heap[child/2] = swap;
      child = child/2;                // become the parent
   }
   return;
}

void print_array(int * x, int n){
	for (int * y = x; y < x + n; y ++){
		printf("%d ", *y);
	}
	putchar('\n');
}

int main(void){
	print_array(heap, N);	

	for (int i = 1; i < N; i ++){
		printf("working on %d...\n", *(heap + i));
		fixUp(heap, i);
	}

	print_array(heap, N);

	return EXIT_SUCCESS;
}
