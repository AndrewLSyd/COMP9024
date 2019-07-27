// ordered word ladders assignment
// COMP9024 Andrew Lau z3330164

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "Graph.h"

#define MAX_STRINGS 1000
#define MAX_CHAR 50
#define DEL_CHAR -1 // sentinel to indicate char is to be deleted
#define ASCII_START 97  // letter a lowercase in ASCII code
#define ASCII_END 122  // letter z lowercasein ASCII code

int differByOne(char * char_1_ptr, char * char_2_ptr);
int readDict(char my_dict[MAX_STRINGS][MAX_CHAR]);
void printDict(char my_dict[MAX_STRINGS][MAX_CHAR], int num_words);

// test suite
int testDifferByOne(void);

int main(void){
    puts("running owl.c ...\n");
    puts("testing differByOne()");
    testDifferByOne();

    // read strings into an array of strings
    int num_words;
    char my_dict[MAX_STRINGS][MAX_CHAR];
    num_words = readDict(my_dict);
    printf("number of words read in is %d\n", num_words);
    printDict(my_dict, num_words);
    return EXIT_SUCCESS;
}

int readDict(char my_dict[MAX_STRINGS][MAX_CHAR]) {
// reads strings from stdin into an array of strings and returns a pointer to it
    int dict_ctr = 0;
    int num_words = 0;
    while (scanf("%s", my_dict[dict_ctr]) != EOF) {
        printf("reading in %s\n", my_dict[dict_ctr]);
        dict_ctr ++;
        num_words += 1;
    }
    return num_words;
}

void printDict(char my_dict[MAX_STRINGS][MAX_CHAR], int num_words){
    fprintf(stdout, "Dictionary\n");
    for (int i=0; i < num_words; i++){
        printf("%d: %s\n", i, my_dict[i]);
    }
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
        for (int lp_chg_1=0; lp_chg_1 < strlen(char_2_ptr); lp_chg_1++){
            strcpy(char_2_cpy_ptr, char_2_ptr);
            // printf("made a copy of %s, %s\n", char_2_ptr, char_2_cpy_ptr);
            // printf("permuting the %dth letter:\n", i);
            for (int lp_add_2=ASCII_START; lp_add_2 <= ASCII_END; lp_add_2++){  // loop through lower case [a-z]
                char_2_cpy_ptr[lp_chg_1] = lp_add_2;
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
        for (int lp_del_1=0; lp_del_1 < strlen(char_1_ptr); lp_del_1++){  // loop through and del one char at a time
            strcpy(char_temp_cpy_ptr, char_1_ptr);
            // remove ith char
            *(char_temp_cpy_ptr + lp_del_1) = DEL_CHAR;

            // copy over new string with deleted char
            int mkr_del=0;  // marker for char_1_cpy_ptr
            for (int lp_del_2=0; *(char_temp_cpy_ptr + lp_del_2 ) != '\0'; lp_del_2++){
                if (*(char_temp_cpy_ptr + lp_del_2 ) != DEL_CHAR){  // if not DEL_CHAR sentinal
                    *(char_1_cpy_ptr + mkr_del) = *(char_temp_cpy_ptr + lp_del_2 );
                    mkr_del++;
                }
            }
            *(char_1_cpy_ptr + mkr_del) = '\0';  // add sentinel

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
        for (int lp_add_1=0; lp_add_1 < strlen(char_1_ptr) + 1; lp_add_1++){
            // loop through alphabet [a-z]
            for (int lp_add_2=ASCII_START; lp_add_2 <= ASCII_END; lp_add_2++){  // loop through lower case [a-z]{
                // copy over new string with deleted char
                int mkr_add=0;  // marker for char_1_cpy_ptr
                for (int k=0; k < strlen(char_1_ptr) + 1; k++){
                    if (k == lp_add_1){  // if  we are at the position to add a char
                        *(char_1_cpy_ptr + mkr_add) = lp_add_2;
                        mkr_add++;
                    }
                    *(char_1_cpy_ptr + mkr_add) = *(char_1_ptr + k );
                    mkr_add++;
                }
                *(char_1_cpy_ptr + lp_add_2) = '\0';  // add sentinel
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
    char * bran = "bran";
    char * ran = "ran";
    char * shave = "shave";
    
    // char * bear = "bear";
    // char * beat = "beat";
    char * beer = "beer";
    char * dear = "dear";
    char * deer = "deer";
    char * fear = "fear";
    char * feat = "feat";
    char * hear = "hear";
    // char * heat = "heat";
    // char * meat = "meat";
    char * near = "near";
    // char * neat = "neat";
    char * pear = "pear";
    char * rear = "rear";
    // char * seat = "seat";
    char * tear = "tear";
    char * wear = "wear";
    char * year = "year";
    
    int total = 0;
    int correct = 0;

    // should return 1
    testDifferByOneHelper(test_1, test_2, 1, &total, &correct);
    testDifferByOneHelper(test_3, test_4, 3, &total, &correct);
    testDifferByOneHelper(test_6, test_9, 1, &total, &correct);
    testDifferByOneHelper(test_1, test_5, 1, &total, &correct);
    testDifferByOneHelper(test_10, test_11, 3, &total, &correct);
    testDifferByOneHelper(bran, ran, 2, &total, &correct);
    testDifferByOneHelper(shave, test_10, 2, &total, &correct);
    
    testDifferByOneHelper("bear", "dear", 1, &total, &correct);
    testDifferByOneHelper(dear, fear, 1, &total, &correct);
    testDifferByOneHelper(fear, hear, 1, &total, &correct);
    testDifferByOneHelper(hear, near, 1, &total, &correct);
    testDifferByOneHelper(near, pear, 1, &total, &correct);
    testDifferByOneHelper(pear, rear, 1, &total, &correct);
    testDifferByOneHelper(rear, tear, 1, &total, &correct);
    testDifferByOneHelper(tear, wear, 1, &total, &correct);
    testDifferByOneHelper(wear, tear, 1, &total, &correct);
    testDifferByOneHelper(rear, year, 1, &total, &correct);


    // should return 0
    testDifferByOneHelper(test_1, test_3, 0, &total, &correct);
    testDifferByOneHelper(test_1, test_4, 0, &total, &correct);
    testDifferByOneHelper(test_3, test_5, 0, &total, &correct);
    testDifferByOneHelper(test_4, test_7, 0, &total, &correct);
    testDifferByOneHelper(test_1, test_8, 0, &total, &correct);
    testDifferByOneHelper(feat, tear, 0, &total, &correct);
    testDifferByOneHelper(shave, wear, 0, &total, &correct);
    testDifferByOneHelper(beer, tear, 0, &total, &correct);
    testDifferByOneHelper("beer", "tear", 0, &total, &correct);
    testDifferByOneHelper(deer, year, 0, &total, &correct);
    printf("successes: %d, failures: %d, total: %d\n", correct, total - correct, total);
    return EXIT_SUCCESS;
}