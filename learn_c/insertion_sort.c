// insertion sort algorithm in C
#include <stdio.h>
#include <stdlib.h>

int ARRAY[] = {5, 3, 7, 8, 4, 13, 2, 10};
#define N 7

int int_swap(int * a, int *b);

void print_array(int array[], int length){
    int i;
    for (i = 0; i < length; i ++){
    printf(" %d", array[i]);
    }
}

int ins_sort(int x[], int n){
    // insertion sort
    // x[] is the array to be sorted
    // n is the length of the array
    // operates in input in place
    int i, j;
    for (i = 1; i < n; i ++){ // loop through from first element to last
        for (j = i - 1; j >= 0; j --){ // for each element, swap items if out of order
            if (x[j] > x[j + 1]){ // if it is out of place swap until it is in place
                int_swap(&x[j], &x[j + 1]);
            }
        }
        printf("\ni = %d\n", i);
        print_array(ARRAY, N);
    }
    return EXIT_SUCCESS;
}

int main(void){
    puts("running insertion sort on:");
    print_array(ARRAY, N);
    ins_sort(ARRAY, N);
    puts("\nsorted array is:");
    print_array(ARRAY, N);
    puts("\n");
    return EXIT_SUCCESS;
}