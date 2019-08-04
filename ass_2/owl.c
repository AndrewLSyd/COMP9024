// ordered word ladders assignment
// COMP9024 Andrew Lau z3330164
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <string.h>
#include "Graph.h"
#include "Quack.h"

#define MAX_WORDS 1005  // max number of words in dictionary (max vertices)
#define MAX_CHAR 25  // max characters per word in dictionary
#define MAX_PATHS 1000  // max number of paths we can search
#define SENTINEL -1 // sentinel to indicate end of something (used in various places)
#define UNVISITED -1  // -1 to indicated invisted vertex for BFS
#define ASCII_START 97  // letter a lowercase in ASCII code
#define ASCII_END 122  // letter z lowercasein ASCII code
#define ERROR_MEMORY "ERROR: malloc failed... out of memory\n"

// function prototypes for main OWL program
int differByOne(char * char_1_ptr, char * char_2_ptr);
int readDict(char my_dict[MAX_WORDS][MAX_CHAR]);
void printDict(char my_dict[MAX_WORDS][MAX_CHAR], int num_words);
int readIntoGraph(int numV, Graph g, char dict[MAX_WORDS][MAX_CHAR], int verbose) ;
void shortestPath(Graph g, Vertex start, Vertex goal, int numV);
void dfsR(Graph g, Vertex v, int numV, char my_dict[MAX_WORDS][MAX_CHAR], char * pathList_StrPrnt,
    char pathList_intStr[MAX_PATHS][MAX_WORDS], char path_intStr[MAX_WORDS], int * path_num_ptr,
    int * path_intArray_ptr, int * pathList_intArray_ptr);
void printPathListStrInt(char pathList_intStr[MAX_PATHS][MAX_WORDS], char dict[MAX_WORDS][MAX_CHAR]);
void printPathStrInt(char * path_ptr, char dict[MAX_WORDS][MAX_CHAR]);
void printPathInt(int * path_ptr, char dict[MAX_WORDS][MAX_CHAR]);
void printPathListInt(int * pathList_intStr, char dict[MAX_WORDS][MAX_CHAR]);

// helper function prototypes
void printArray_char(char * prefix, int * array_ptr, int n);
int * intdup(int * src, int len);
void checkMalloc(void * ptr);
void printArray_int(char * prefix, int * array_ptr, int n);

// function prototypes for test suite   
int testDifferByOne(int verbose);

int main(void){
    puts("running owl.c ...\n");
    puts("testing differByOne()");
    testDifferByOne(0);

    // read strings into an array of strings
    int num_words;
    char my_dict[MAX_WORDS][MAX_CHAR];
    num_words = readDict(my_dict);    
    printDict(my_dict, num_words);
    printf("num_words %d", num_words);

    Graph g = newGraph(num_words);
    fprintf(stdout, "Ordered Word Ladder Graph\n");    
    readIntoGraph(num_words, g, my_dict, 0);
    showGraph(g);

    // initialising paths
    char path_intStr[MAX_WORDS] = "";
    int * path_intArray = NULL;
    path_intArray = malloc(MAX_WORDS * sizeof(int));    
    checkMalloc(path_intArray);  // function that checks if NULL was returned by malloc

    // initialising path list (used to store path in reursive DFS calls)
    char pathList_StrPrnt[10000] = "";    
    char pathList_intStr[MAX_PATHS][MAX_WORDS];
    int * pathList_intArray_ptr = NULL;
    pathList_intArray_ptr = malloc(MAX_PATHS * MAX_WORDS * sizeof(int));
    checkMalloc(pathList_intArray_ptr);  // function that checks if NULL was returned by malloc

    // initialise paths all to sentinels (just in case)
    for (int i=0; i < MAX_PATHS; i ++){
        for (int j=0; j < MAX_WORDS; j ++){
            pathList_intStr[i][j] = '\0';        
            *(pathList_intArray_ptr + i * MAX_WORDS + j) = SENTINEL;
        }
    }
    for (int k=0; k < MAX_WORDS; k++){
        *(path_intArray + k) = SENTINEL;
    }


    // printPathInt
    // *(pathList_intArray_ptr + 0) = 10;
    // *(pathList_intArray_ptr + 1) = 9;
    // *(pathList_intArray_ptr + 2) = 8;
    // *(pathList_intArray_ptr + 3) = 7;

    // *(pathList_intArray_ptr + MAX_WORDS + 0) = 7;
    // *(pathList_intArray_ptr + MAX_WORDS + 1) = 6;
    // *(pathList_intArray_ptr + MAX_WORDS + 2) = 5;
    // *(pathList_intArray_ptr + MAX_WORDS + 3) = 4;


    // printPathInt(pathList_intArray_ptr, my_dict);
    // printPathInt(pathList_intArray_ptr + MAX_WORDS, my_dict);
    // printPathListInt(pathList_intArray_ptr, my_dict);

    int path_num = 0;
    // loop DFS search over all vertices
    // printPathListStrInt(pathList_intStr, my_dict);
    for (int vertex=0; vertex < num_words; vertex ++){
        dfsR(g, vertex, num_words, my_dict, pathList_StrPrnt, pathList_intStr, path_intStr, &path_num, path_intArray, pathList_intArray_ptr);
    }
    // printPathListStrInt(pathList_intStr, my_dict);
    printPathListInt(pathList_intArray_ptr, my_dict);


    puts("START FINDING MAX PATH...\n");
    // step 1: create array that has the lenths of all the paths
    int * pathLengths_intArray_ptr = NULL;
    pathLengths_intArray_ptr = malloc(MAX_PATHS * sizeof(int));
    for (int lp_pliap=0; lp_pliap < MAX_PATHS; lp_pliap ++){
        *(pathLengths_intArray_ptr + lp_pliap) = SENTINEL;
    }
    
    // step 2: find length of all the paths
    int * path_ptr = pathList_intArray_ptr;
    int path_counter = 0;
    int max_len = 0;

    while (*(path_ptr) != SENTINEL){  // loop across paths
        int * word_ptr = path_ptr;
        int word_counter = 0;
        while (*word_ptr != SENTINEL){  // loop across words in each path to find the path length
            word_counter ++;
            word_ptr ++;
        }
        *(pathLengths_intArray_ptr + path_counter) = word_counter;
        if (word_counter > max_len){
            max_len = word_counter;
        }
        // printf("PATH %d: %s -> ... length %d. max_len = %d\n", path_counter, my_dict[*(path_ptr)], word_counter, max_len);
        path_counter++;
        path_ptr += MAX_WORDS;  // next path
    }

    printArray_int("pathLengths_intArray_ptr", pathLengths_intArray_ptr, MAX_PATHS);

    // step 3: print out paths with max lengths
    for (int lp_iap2=0; *(pathLengths_intArray_ptr + lp_iap2) != SENTINEL; lp_iap2++){
        if (*(pathLengths_intArray_ptr + lp_iap2) == max_len){            
            printPathInt(pathList_intArray_ptr + lp_iap2 * MAX_WORDS, my_dict);   
        }
    } 

    // int path_len[MAX_PATHS] = {0};

    // for (int l=0; l < MAX_PATHS; l++){
    //     if (*pathList_intStr[l] != '\0'){
    //         printf(" %s", pathList_intStr[l]);
    //         printPathStrInt(pathList_intStr[l], my_dict);
    //     }
    // } 
  
    return EXIT_SUCCESS;
}

void dfsR(
    // use recursive DFS to search ALL possible paths in the tree
    // a temp_str pointer is passed to each recursive function call
    // and once a leaf node is reached, this string representing
    // the entire path is saved into an array representing all possible paths
    // inputs:
    Graph g,  // g is a ptr to the graph
    Vertex v,
    int numV,  // numV is the number of vertices in the graph
    char my_dict[MAX_WORDS][MAX_CHAR],  // my_dict is the dictionary of words
    char * pathList_StrPrnt,  // pathList_StrPrnt is a string representation of the path
    char pathList_intStr[MAX_PATHS][MAX_WORDS],
    char path_intStr[MAX_WORDS],
    int * path_num_ptr,
    int * path_intArray_ptr,
    int * pathList_intArray_ptr) {        
    
    int has_children = 0;
    char temp_str[100000];
    char temp_str_int[MAX_WORDS];
    int * temp_int_arr_ptr = NULL;
    
    // make a copy of the current path in the recursion
    strcpy(temp_str, pathList_StrPrnt);
    strcpy(temp_str_int, path_intStr);
    temp_int_arr_ptr = intdup(path_intArray_ptr, MAX_WORDS);

    // add current node to current path in recursion
    strcat(temp_str, "->");    
    strcat(temp_str, my_dict[v]);
    int i=0;
    while (temp_str_int[i] != '\0'){
        i ++;
    }
    temp_str_int[i] = v + '0';
    temp_str_int[i + 1] = '\0';

    // ERROR IS HAPPENING AFTER HERE
    int lp_iap=0;
    while (*(temp_int_arr_ptr + lp_iap) != SENTINEL){        
        lp_iap ++;
    }
    *(temp_int_arr_ptr + lp_iap) = v;
    // ERROR IS HAPPENING BEOFRE HERE
        
    // find child nodes (connected and child nodes > parent)
    for (Vertex w = 0; w < numV; w++) {
        // printf("isEdge(%s, %s), %d\n", my_dict[v], my_dict[w], isEdge(newEdge(v,w), g))  ;          
        if (isEdge(newEdge(v,w), g) && w > v) {            
            has_children = 1;
            dfsR(g, w, numV, my_dict, temp_str, pathList_intStr, temp_str_int, path_num_ptr, temp_int_arr_ptr,
                pathList_intArray_ptr);            
      }
   }
   if (has_children == 0){  // e.g. if leaf node
        // save full path in path list
        printf("PATH: %s\n", temp_str);
        strcpy(pathList_intStr[*path_num_ptr], temp_str_int);
        int * path_ptr = (pathList_intArray_ptr + MAX_WORDS * (*path_num_ptr));
        for (int lp_path_ptr=0; *(temp_int_arr_ptr + lp_path_ptr) != SENTINEL; lp_path_ptr++){
            *path_ptr =  *(temp_int_arr_ptr + lp_path_ptr);
            path_ptr ++;
        }
        (*path_num_ptr) ++;
   }
  
   return;
}


int readIntoGraph(int numV, Graph g, char dict[MAX_WORDS][MAX_CHAR], int verbose) {
    // input: number of vertices, pointer to graph
    // returns: pointer to the graph with edges added
    int success = 0;             // returns true if no error
    int dbo;

    // double loop to pairwise check if there is an edge
    for (int lp_readgraph_1=0; lp_readgraph_1 < numV; lp_readgraph_1 ++){        
        for (int lp_readgraph_2=0; lp_readgraph_2 < numV; lp_readgraph_2 ++){    
            if (strcmp(dict[lp_readgraph_1], dict[lp_readgraph_2]) != 0){  // if the words are different
                dbo = differByOne(dict[lp_readgraph_1], dict[lp_readgraph_2]);
                if (dbo){
                    insertEdge(newEdge(lp_readgraph_1, lp_readgraph_2), g);
                    success = 1;
                }
                if (verbose){
                    printf("differByOne %d: %s, %d: %s... %d\n", lp_readgraph_1, dict[lp_readgraph_1], lp_readgraph_2,
                        dict[lp_readgraph_2], dbo);            
                }
            }
        }
    }
    return success;
}

int readDict(char my_dict[MAX_WORDS][MAX_CHAR]) {
    // reads strings from stdin into an array of strings and returns a pointer to it
    int dict_ctr = 0;
    int num_words = 0;
    while (scanf("%s", my_dict[dict_ctr]) != EOF) {
        // printf("reading in %s\n", my_dict[dict_ctr]);
        dict_ctr ++;
        num_words += 1;
    }
    return num_words;
}

void printDict(char my_dict[MAX_WORDS][MAX_CHAR], int num_words){
    // inputs: array of strings, number of words
    // returns: void. prints the dictionary.
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
    // check if malloc was successful
    if (char_1_cpy_ptr == NULL || char_2_cpy_ptr == NULL || char_temp_cpy_ptr == NULL) {
        fprintf(stderr, ERROR_MEMORY);
        exit(1);
    }

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
            *(char_temp_cpy_ptr + lp_del_1) = SENTINEL;

            // copy over new string with deleted char
            int mkr_del=0;  // marker for char_1_cpy_ptr
            for (int lp_del_2=0; *(char_temp_cpy_ptr + lp_del_2 ) != '\0'; lp_del_2++){
                if (*(char_temp_cpy_ptr + lp_del_2 ) != SENTINEL){  // if not SENTINEL sentinal
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
        strcpy(char_1_cpy_ptr, char_1_ptr);
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
                *(char_1_cpy_ptr + mkr_add) = '\0';  // add sentinel
                // printf("char_1_cpy_ptr is %s,  char_1_ptr is %s\n",  char_1_cpy_ptr, char_1_ptr) ;
                if (strcmp(char_1_cpy_ptr, char_2_ptr) == 0){
                    dbo = 3;
                }
            }
        }
    }

    return dbo;
}


void printPathInt(int * path_ptr, char dict[MAX_WORDS][MAX_CHAR]){
    // inputs: path_ptr is a pointer to an int array representation of the path, e.g. {0, 1, 3, 6} is
        // word_0 -> word_1 -> word_3 -> word_6
    // purpose: prints out the word path (natural langauge version)    
    int word_count = 0;
    for (int word=0; word < MAX_WORDS; word++){
        if (*(path_ptr + word) != SENTINEL){                    
            printf("-> %s ", dict[*(path_ptr + word)]);
            word_count ++;          
        }            
    }
    printf(" (%d) \n", word_count);      
}

void printPathListInt(int * path_ptr, char dict[MAX_WORDS][MAX_CHAR]){
    // inputs: 2D int array ptr
    // purpose: prints out the word path of all paths in my_path    
    puts("printPathListInt");
    int word_count = 0;
    for (int path=0; path < MAX_PATHS; path++){
        if (*(path_ptr + MAX_WORDS * path) != SENTINEL){
            word_count = 0;
            printf("PATH %d: ", path);
            printPathInt((path_ptr + MAX_WORDS * path), dict);
        }
    }
}

void printPathStrInt(char * path_ptr, char dict[MAX_WORDS][MAX_CHAR]){
    // inputs: path_ptr is a pointer to a str representation of the path, e.g. '0136' is
        // word_0 -> word_1 -> word_3 -> word_6
        // dict is the array of strings representing our input dictionary
    // purpose: prints out the word path (natural langauge version)
    // if (*(path_ptr) != '\0'){        
        int word_count = 0;
        for (int word=0; word < MAX_WORDS; word++){
            if (*(path_ptr + word) != '\0'){                    
                printf("-> %s ", dict[*(path_ptr + word) - '0']);
                word_count ++;          
            }            
        }
        printf(" (%d) \n", word_count);      
    // }
}

void printPathListStrInt(char pathList_intStr[MAX_PATHS][MAX_WORDS], char dict[MAX_WORDS][MAX_CHAR]){
    // inputs: array of strings representing paths
    // purpose: prints out the word path of all paths in my_path
    puts("printPathListStrInt\n");
    int word_count = 0;
    for (int path=0; path < MAX_PATHS; path++){
        if (pathList_intStr[path][0] != '\0'){
            word_count = 0;
            printf("PATH %d: ", path);
            printPathStrInt(pathList_intStr[path], dict);
        }
    }
}

void printPath(int parent[], int numV, Vertex v) {
   if (parent[v] != UNVISITED) { // parent of start is UNVISITED
      if (0 <= v && v < numV) {
         printPath(parent, numV, parent[v]);
         printf("-->");
      }
      else {
         fprintf(stderr, "\nprintPath: invalid goal %d\n", v);
      }
   }
   printf("%d", v); // the last call will print here first
   return;
}

//   _   _      _                    __                  _   _                 
//  | | | | ___| |_ __   ___ _ __   / _|_   _ _ __   ___| |_(_) ___  _ __  ___ 
//  | |_| |/ _ \ | '_ \ / _ \ '__| | |_| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
//  |  _  |  __/ | |_) |  __/ |    |  _| |_| | | | | (__| |_| | (_) | | | \__ \
//  |_| |_|\___|_| .__/ \___|_|    |_|  \__,_|_| |_|\___|\__|_|\___/|_| |_|___/
//               |_|                                                           
void printArray_char(char * prefix, int * array_ptr, int n){
    // inputs: char ptr to a string for the prefix, int ptr to an array we want to print,
        // number of elements in array
    // prints array with a prefix
    printf("%s", prefix);
    printf("{%d", *array_ptr);
    for (int i=1; i < n; i++){
        printf(", %d", *(array_ptr + i));
    }
    fprintf(stdout, "}\n");
}

void printArray_int(char * prefix, int * array_ptr, int n){
    // inputs: char ptr to a string for the prefix, int ptr to an array we want to print,
        // number of elements in array
    // prints array with a prefix
    printf("%s", prefix);
    printf("{%d", *array_ptr);
    for (int i=1; i < n; i++){
        printf(", %d", *(array_ptr + i));
    }
    fprintf(stdout, "}\n");
}

int * intdup(int * src, int len)
{
   int * p = malloc(len * sizeof(int));
   memcpy(p, src, len * sizeof(int));
   return p;
}

void checkMalloc(void * ptr){
    // input: pointer
    // checks if malloc worked (e.g. NULL not returned)
    if (ptr == NULL){
        fprintf(stderr, ERROR_MEMORY);
        exit(1);
    }   
}
//   _____         _       
//  |_   _|__  ___| |_ ___ 
//    | |/ _ \/ __| __/ __|
//    | |  __/\__ \ |_\__ \
//    |_|\___||___/\__|___/
// Albert/Harrison you can ignore these

void testDifferByOneHelper(char * x, char * y, int expected, int * total, int * correct, int verbose){
    // input: two char ptrs and expected result to differByOne
    // output: increments total and correct appropriately
    *total += 1;
    int result = differByOne(x, y);
    // if (result != differByOne(y, x)){
    //     puts("\tassymetry error");
    //     return;
    // }
    if (verbose){
        printf("  (%s, %s), exp: %d, act: %d...", x, y, expected, result);
    }
    if (result == expected){
        *correct += 1;
        if (result == 0){
            if (verbose){
                fprintf(stdout, " success (not DBO)\n");
            }
        }
        if (result == 1){
            if (verbose){
                fprintf(stdout, " success (DBO change 1 letter)\n");
            }
        }
        else if (result == 2){
            if (verbose){
                fprintf(stdout, " success (DBO del 1 letter)\n");
            }
        }
        else if (result == 3){
            if (verbose){
                fprintf(stdout, " success (DBO add 1 letter)\n");
            }
        }
    }
    else{
        fprintf(stdout, " FAILURE\n");
    }
}

int testDifferByOne(int verbose){
    // test function with built in cases for DifferByOneFunction
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
    testDifferByOneHelper(test_1, test_2, 1, &total, &correct, verbose);
    testDifferByOneHelper(test_3, test_4, 3, &total, &correct, verbose);
    testDifferByOneHelper(test_6, test_9, 1, &total, &correct, verbose);
    testDifferByOneHelper(test_1, test_5, 1, &total, &correct, verbose);
    testDifferByOneHelper(test_10, test_11, 3, &total, &correct, verbose);
    testDifferByOneHelper(bran, ran, 2, &total, &correct, verbose);
    testDifferByOneHelper(shave, test_10, 2, &total, &correct, verbose);
    
    testDifferByOneHelper("bear", "dear", 1, &total, &correct, verbose);
    testDifferByOneHelper(dear, fear, 1, &total, &correct, verbose);
    testDifferByOneHelper(fear, hear, 1, &total, &correct, verbose);
    testDifferByOneHelper(hear, near, 1, &total, &correct, verbose);
    testDifferByOneHelper(near, pear, 1, &total, &correct, verbose);
    testDifferByOneHelper(pear, rear, 1, &total, &correct, verbose);
    testDifferByOneHelper(rear, tear, 1, &total, &correct, verbose);
    testDifferByOneHelper(tear, wear, 1, &total, &correct, verbose);
    testDifferByOneHelper(wear, tear, 1, &total, &correct, verbose);
    testDifferByOneHelper(rear, year, 1, &total, &correct, verbose);


    // should return 0
    testDifferByOneHelper(test_1, test_3, 0, &total, &correct, verbose);
    testDifferByOneHelper(test_1, test_4, 0, &total, &correct, verbose);
    testDifferByOneHelper(test_3, test_5, 0, &total, &correct, verbose);
    testDifferByOneHelper(test_4, test_7, 0, &total, &correct, verbose);
    testDifferByOneHelper(test_1, test_8, 0, &total, &correct, verbose);
    testDifferByOneHelper(feat, tear, 0, &total, &correct, verbose);
    testDifferByOneHelper(shave, wear, 0, &total, &correct, verbose);
    testDifferByOneHelper(beer, tear, 0, &total, &correct, verbose);
    testDifferByOneHelper("beer", "tear", 0, &total, &correct, verbose);
    testDifferByOneHelper(deer, year, 0, &total, &correct, verbose);
    printf("successes: %d, failures: %d, total: %d\n", correct, total - correct, total);
    return EXIT_SUCCESS;
}
