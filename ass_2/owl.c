// ordered word ladders assignment
// COMP9024 Andrew Lau z3330164

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_CHAR 200
#define DEL_CHAR -1 // sentinel to indicate char is to be deleted
#define ASCII_START 97  // letter a lowercase in ASCII code
#define ASCII_END 122  // letter z lowercasein ASCII code

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
    // inputs: 2 char pointers, all lower case alpha chars
        // checks by permuting SECOND argument
        // e.g. checks FORWARD changes
    // returns:
        // 0 if doesn't differ by one
        // 1 if differs by one by changing one char
        // 2 if differs by one by deleting one char
        // 3 if differs by one by adding one char
    int dbo = 0;
    // make a copy of char_2 to permute
    char * char_1_cpy_ptr = malloc(MAX_CHAR * sizeof(char));
    char * char_2_cpy_ptr = malloc(MAX_CHAR * sizeof(char));
    char * char_temp_cpy_ptr = malloc(MAX_CHAR * sizeof(char));

    // case 1: same number of character. need to test by changing letters one by one
    if (strlen(char_1_ptr) == strlen(char_2_ptr)){
        // hold char_1 constant and permute char_2
        for (int i=0; i < strlen(char_2_ptr); i++){
            strcpy(char_2_cpy_ptr, char_2_ptr);
            // printf("made a copy of %s, %s\n", char_2_ptr, char_2_cpy_ptr);
            // printf("permuting the %dth letter:\n", i);
            for (int j=ASCII_START; j <= ASCII_END; j++){  // loop through lower case [a-z]
                char_2_cpy_ptr[i] = j;
                // printf("%s, ", char_2_cpy_ptr);
                if (strcmp(char_2_cpy_ptr, char_1_ptr) == 0){
                    // printf("\t\tSUCCESS: changing 1 letter in %s gives us %s\n", char_2_ptr, char_1_ptr);
                    dbo = 1;
                }
            }
        }
    }
    // case 2: removing a character
    // cat -> at, ct, ca
    else if (strlen(char_1_ptr) - strlen(char_2_ptr) == 1){  // only check if char_2 has one less char
        // puts("CHECKING REMOVE 1 CHAR");
        for (int i=0; i < strlen(char_1_ptr); i++){  // loop through and del one char at a time
            strcpy(char_temp_cpy_ptr, char_1_ptr);
            // remove ith char
            *(char_temp_cpy_ptr + i) = DEL_CHAR;

            // copy over new string with deleted char
            int j=0;  // marker for char_1_cpy_ptr
            for (int i=0; *(char_temp_cpy_ptr + i ) != '\0'; i++){
                if (*(char_temp_cpy_ptr + i ) != DEL_CHAR){  // if not DEL_CHAR sentinal
                    *(char_1_cpy_ptr + j) = *(char_temp_cpy_ptr + i );
                    j++;
                }
            }
            *(char_1_cpy_ptr + j) = '\0';  // add sentinel

            // printf("\t\t\tchecking remove one char %s vs %s\n", char_1_cpy_ptr, char_2_ptr);
            if (strcmp(char_1_cpy_ptr, char_2_ptr) == 0){
                // printf("\t\tSUCCESS: deleting 1 letter in %s gives us %s\n", char_1_ptr, char_2_ptr);
                dbo = 2;
            }
        }
    }
    // case 3: adding a character
    // cat -> Xcat, cXat, caXt, catX
    else if (strlen(char_1_ptr) - strlen(char_2_ptr) == -1){  // only check if char_2 has one more char
        // loop through and add one char at a time
        // i is the position where we add a char:
        //  c a t
        // ^ ^ ^ ^
        // 0 1 2 3
        for (int i=0; i < strlen(char_1_ptr) + 1; i++){
            // loop through alphabet [a-z]
            for (int j=ASCII_START; j <= ASCII_END; j++){  // loop through lower case [a-z]{
                // copy over new string with deleted char
                int marker=0;  // marker for char_1_cpy_ptr
                for (int k=0; k < strlen(char_1_ptr) + 1; k++){
                    if (k == i){  // if  we are at the position to add a char
                        *(char_1_cpy_ptr + marker) = j;
                        marker++;
                    }
                    *(char_1_cpy_ptr + marker) = *(char_1_ptr + k );
                    marker++;
                }
                *(char_1_cpy_ptr + j) = '\0';  // add sentinel
                // printf("char_1_cpy_ptr is %s,  char_1_ptr is %s\n",  char_1_cpy_ptr, char_1_ptr) ;
                if (strcmp(char_1_cpy_ptr, char_2_ptr) == 0){
                    dbo = 3;
                }
            }
        }
    }

    return dbo;
}

// test suite below
void testDifferByOneHelper(char * x, char * y, int expected, int * total, int * correct){
    // input: two char ptrs and expected result to differByOne
    // output: increments total and correct appropriately
    *total += 1;
    int result = differByOne(x, y);
    // if (result != differByOne(y, x)){
    //     puts("\tassymetry error");
    //     return;
    // }
    printf("  (%s, %s), exp: %d, act: %d...", x, y, expected, result);
    if (result == expected){
        *correct += 1;
        if (result == 0){
            fprintf(stdout, " success (not DBO)\n");
        }
        if (result == 1){
            fprintf(stdout, " success (DBO change 1 letter)\n");
        }
        else if (result == 2){
            fprintf(stdout, " success (DBO del 1 letter)\n");
        }
        else if (result == 3){
            fprintf(stdout, " success (DBO add 1 letter)\n");
        }
    }
    else{
        fprintf(stdout, " FAILURE\n");
    }
}

int testDifferByOne(void){
    char * test_1 = "case";
    char * test_2 = "cast";
    char * test_3 = "cat";
    char * test_4 = "cats";
    char * test_5 = "cave";
    char * test_6 = "cost";
    char * test_7 = "cove";
    char * test_8 = "love";
    char * test_9 = "post";
    char * test_10 = "save";
    char * test_11 = "suave";
    char * BRAN = "bran";
    char * RAN = "ran";
    char * SHAVE = "shave";

    int total = 0;
    int correct = 0;

    // should return 1
    testDifferByOneHelper(test_1, test_2, 1, &total, &correct);
    testDifferByOneHelper(test_3, test_4, 3, &total, &correct);
    testDifferByOneHelper(test_6, test_9, 1, &total, &correct);
    testDifferByOneHelper(test_1, test_5, 1, &total, &correct);
    testDifferByOneHelper(test_10, test_11, 3, &total, &correct);
    testDifferByOneHelper(BRAN, RAN, 2, &total, &correct);
    testDifferByOneHelper(SHAVE, test_10, 2, &total, &correct);

    // should return 0
    testDifferByOneHelper(test_1, test_3, 0, &total, &correct);
    testDifferByOneHelper(test_1, test_4, 0, &total, &correct);
    testDifferByOneHelper(test_3, test_5, 0, &total, &correct);
    testDifferByOneHelper(test_4, test_7, 0, &total, &correct);
    testDifferByOneHelper(test_1, test_8, 0, &total, &correct);
    printf("successes: %d, failures: %d, total: %d\n", correct, total - correct, total);
    return EXIT_SUCCESS;
}