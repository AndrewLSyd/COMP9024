// ordered word ladders assignment
// COMP9024 Andrew Lau z3330164

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int differByOne(char * char_1_ptr, char * char_2_ptr);
int lenStr(char * char_ptr);
// test suite
int testDifferByOne(void);

int main(void){
    puts("running owl.c ...\n");
    puts("testing differByOne()");
    testDifferByOne();
    return EXIT_SUCCESS;
}

int differByOne(char * char_1_ptr, char * char_2_ptr){
    // inputs: 2 char pointers
    // returns: 1 if differs by one, 0 otherwise
    int dbo = 0;
    // case 1: same number of character. need to test by changing letters one by one
    if (strlen(char_1_ptr) == strlen(char_2_ptr)){
        char * char_1_cpy_ptr = malloc(200 * sizeof(char));
        char * char_2_cpy_ptr = malloc(200 * sizeof(char));

        strcpy(char_1_cpy_ptr, char_1_ptr);
        strcpy(char_2_cpy_ptr, char_2_ptr);
        
        printf("made a copy of %s, %s\n", char_1_ptr, char_1_cpy_ptr);

        

        // hold char_2 constant and permute char_1
        // for (char * letter_ptr = char_1_ptr, )
    }
    return dbo;
}

// test suite below
void testDifferByOneHelper(char * x, char * y, int expected, int * total, int * correct){
    // input: two char ptrs and expected result to differByOne
    // output: increments total and correct appropriately
    *total += 1;
    int result = differByOne(x, y);
    if (result != differByOne(y, x)){
        puts("\tassymetry error");
        return;
    }
    printf("\tdifferByOne(%s, %s), expected: %d, actual: %d\n", x, y, expected, result);
    if (result == expected){
        *correct += 1;
    }
}

int testDifferByOne(void){
    char * test_1 = "case";
    char * test_2 = "cast";
    char * test_3 = "cat";
    char * test_4 = "cats";
    int total = 0;
    int correct = 0;
    // should return 1
    testDifferByOneHelper(test_1, test_2, 1, &total, &correct);
    testDifferByOneHelper(test_3, test_4, 1, &total, &correct);
    // should return 0
    testDifferByOneHelper(test_1, test_3, 0, &total, &correct);
    testDifferByOneHelper(test_1, test_4, 0, &total, &correct);
    printf("successes: %d, failures: %d, total: %d\n", correct, total - correct, total);
    return EXIT_SUCCESS;
}