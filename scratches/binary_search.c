#include <stdlib.h>
#include <stdio.h>

int ARRAY[] = {1, 2, 4, 5, 6, 7, 10, 12};
#define KEY 3


int bin_search(int array[], int size, int key){
    int found=0, low=0, mid, high=size-1;
    while(!found && low <= high){
        mid = (high + low) / 2;
        if (array[mid] == key){
            found = 1;
        }
        // too high
        else if (array[mid] > key){
            high = mid - 1;
        }
        // too low
        else if (array[mid] < key){
            low = mid + 1;
        }
    }
    return found;
}

int main(void){
    puts("starting program...\n");
    printf("binary search... %d, found: %d", KEY, bin_search(ARRAY, 8, KEY));

    return EXIT_SUCCESS;
}