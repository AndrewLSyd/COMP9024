// boardADT.c - implementation

#include "boardADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

board_t create_board(void){
    // function which creates the board, mallocing mthe required memory
    board_t board;
    board = (board_t) malloc(INITIAL_SIZE * sizeof(int));  // malloc memory
    if (board == NULL) {
        fprintf(stderr, MEMORY_ERROR);
        exit(EXIT_FAILURE);  // exit memory error
    }
    return board;
}

int read_into_board(int ** A){
    // input: a pointer to an int pointer
    // returns number of elements read in, 
    // if a non alpha character is inputted it will be subbed for BLANK
    int n_A = 0;
    double sum, tens;
    char next;
    int malloced_size = INITIAL_SIZE;

    while (scanf("%c", &next) == 1 && next != '\n'){  // while there is input and no new line
        if (next != ' ' && next != '\t'){  // don't capture spaces or tabs
            if (isdigit(next)){  // if there is a number, don't capture leading zeros
                tens = 0;
                sum = next - '0';
                // check for more digits, only engages loop if there is a number
                // while there is input, not a new line and it is a digit
                while (scanf("%c", &next) == 1 && next != '\n' && (isdigit(next))){
                    // the division by ten and tens counter allows capturing of digits with
                    // more than one digit by dividing through by ten. Saved as a double.
                    // machine error shoudln't be an issue with double for numbers not 
                    // too large
                    sum += (next - '0')/ 10.0;  // cast to double
                    tens ++;
                }
                // need to check if need more memory and realloc if needed
                if (n_A == malloced_size - 1){
                    // printf("n_A is %d, malloced_sized is %d\n", n_A, malloced_size);
                    malloced_size = malloced_size * 2;  // double memory allocation
                    *A = (int *) realloc(*A, malloced_size * sizeof(int)); 
                    // printf("malloced_sized is now %d\n", malloced_size);
                    if (*A == NULL) {
                        fprintf(stderr, MEMORY_ERROR);
                        return EXIT_FAILURE;
                    }
                }
                *(*A + n_A) = (int) (sum * pow(10, tens));
                // if new line then return function and increment counter
                if (next == '\n'){
                    n_A += 1;
                    return n_A;
                }
            }
            else if (next == 'b'){
                // need to check if need more memory and realloc if needed
                if (n_A == malloced_size - 1){
                    // printf("n_A is %d, malloced_sized is %d\n", n_A, malloced_size);
                    malloced_size = malloced_size * 2;  // double memory allocation
                    *A = (int *) realloc(*A, malloced_size * sizeof(int));
                    // printf("malloced_sized is now %d\n", malloced_size);
                    if (*A == NULL) {
                        fprintf(stderr, MEMORY_ERROR);
                        return EXIT_FAILURE;
                    }
                }             
                *(*A + n_A) = BLANK;
            }
            else {
                return EXIT_FAILURE;
            }
            n_A += 1;
        }
    }
    return n_A;
}

int calc_disorder(int * B, int n){
    // inputs:
        // *B is an int array pointer that represents a board
        // n is the size of the board (total tiles is n x n)
    // returns: the disorder of the board
    int num_elems = n * n, disorder = 0;

    for (int tile = 0; tile < num_elems; tile ++){
        // *(A + n_A)
        if (*(B + tile) != BLANK){  // don't check BLANK tile
            for (int i = tile + 1; i < num_elems; i ++){
                if (*(B + i) < *(B + tile)){
                    disorder += 1;
                }
            }
        }
        else{  // case when tile is blank
            if (n % 2 == 0){  // if board is even
                int row = tile / n + 1;  //integer  division to get row number
                disorder += row;  // add row number of blank tile to disorder
            }
        }
    }
    return disorder;
}


void print_array(int * array_p, int length){
    // input: an int array pointer, length of array
    // prints the array
    for (int i = 0; i < length; i ++){
        if (*array_p == BLANK){
            fputs(" b", stdout);
        }
        else {
            printf(" %d", *array_p);
        }
        array_p ++;
    }
    fputs("\n", stdout);
}

int check_board(int * A, int num_elems){
    // input: an int array representing a board
    // returns: whether it is "correct" input. EXIT_SUCCESS/EXIT_FAILURE conditions:
        // * 1, 2, ... N-1 and b each appear exactly once
    int value, tile_counter_sum=0;
    int * tile_counter;
    // alloc memory, setting it all to zero
    tile_counter = (int *) calloc((num_elems + 1), sizeof(int)); 
        if (tile_counter == NULL) {
        fprintf(stderr, MEMORY_ERROR);
        return EXIT_FAILURE;
    }

    float difference;

    // num_elems must be a square number. check difference between integer and float
    difference = sqrt(num_elems) - (int) sqrt(num_elems);
    // printf("sqrt(num_elems):, %f (int) sqrt(num_elems): %d, difference: %f\n", sqrt(num_elems), (int) sqrt(num_elems), difference);
    if (fabs(difference) > TOLERANCE){
        puts("Board Input Error: size not square\n");
        // free memory and clear dangling pointer
        free(tile_counter);
        tile_counter = NULL;
        return EXIT_FAILURE;
    }
 
    // loop through each tile in the board counting number of each tile value
    for (int tile=0; tile < num_elems; tile ++){
        value = *(A + tile);
        if (value == BLANK){
            *tile_counter = 1; // first position in array is for blank
        }
        else if (value < 1 || value > num_elems - 1){
            // free memory and clear dangling pointer
            free(tile_counter);
            tile_counter = NULL;
            puts("Board Input Error: input must be between 1 and (N - 1) inclusive.\n");
            return EXIT_FAILURE;
        }
        // otherwise set tile counter for that tile's value to 1
        else {
            * (tile_counter + *(A + tile)) = 1;
        }
    }

    // if board is well formed there should be one of every tile, e.g. sum of array should equal to n
    // count number of each tile value
    for (int i=0; i < num_elems; i ++){
        tile_counter_sum += *(tile_counter + i);
    }
    // puts("TILECOUNTER");
    // print_array(tile_counter, num_elems);
    if (tile_counter_sum == num_elems){
        // free memory and clear dangling pointer
        free(tile_counter);
        tile_counter = NULL;
        return EXIT_SUCCESS;
    }
    else {
        // free memory and clear dangling pointer
        free(tile_counter);
        puts("Board Input Error: there is not exactly 1 of 1, 2, ..., N - 1 and b.\n");
        return EXIT_FAILURE;
    }
}
