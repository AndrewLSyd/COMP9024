// ordered word ladders assignment
// COMP9024 Andrew Lau z3330164
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <string.h>
#include "Graph.h"
#include "Quack.h"

#define MAX_WORDS 2000  // max number of words in dictionary (max vertices)
#define MAX_CHAR 100  // max characters per word in dictionary
#define SENT_DEL -1 // sentinel to indicate char is to be deleted
#define ASCII_START 97  // letter a lowercase in ASCII code
#define ASCII_END 122  // letter z lowercasein ASCII code
#define ERROR_MEMORY "ERROR: malloc failed... out of memory\n"
#define UNVISITED -1  // -1 to indicated invisted vertex for BFS

// function prototypes for main OWL program
int differByOne(char * char_1_ptr, char * char_2_ptr);
int readDict(char my_dict[MAX_WORDS][MAX_CHAR]);
void printDict(char my_dict[MAX_WORDS][MAX_CHAR], int num_words);
int readIntoGraph(int numV, Graph g, char dict[MAX_WORDS][MAX_CHAR], int verbose) ;
void printArray(char * prefix, int * array_ptr, int n);
void shortestPath(Graph g, Vertex start, Vertex goal, int numV);
void dfsR(Graph g, Vertex v, int numV, int depth, char my_dict[MAX_WORDS][MAX_CHAR], char * out_string);

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

    Graph g = newGraph(num_words);
    fprintf(stdout, "Ordered Word Ladder Graph\n");    
    readIntoGraph(num_words, g, my_dict, 0);
    showGraph(g);

    puts("finding shortest path...");

    // shortestPath(Graph g, Vertex start, Vertex goal, int numV)

    // testing print array

    int test[5] = {-1,2,3,4,5};
    printArray("test: ", test, 5);

    shortestPath(g, 0, 4, num_words);

    char out_str[10000] = "";
    dfsR(g, 0, num_words, 0, my_dict, out_str);
    
    return EXIT_SUCCESS;
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


void dfsR(Graph g, Vertex v, int numV, int depth, char my_dict[MAX_WORDS][MAX_CHAR], char * out_string) {
    // need new string each time!!
    char temp_str[10000];
    strcpy(temp_str, out_string);

    strcat(temp_str, "->");
    strcat(temp_str, my_dict[v]);
    // printf(" %d-%s-%d ", v, my_dict[v], depth);   
    int has_children = 0;
    depth += 1;
    // find child nodes (connected and child nodes > parent)
    for (Vertex w = 0; w < numV; w++) {
        // printf("isEdge(%s, %s), %d\n", my_dict[v], my_dict[w], isEdge(newEdge(v,w), g))  ;          
        if (isEdge(newEdge(v,w), g) && w > v) {            
            has_children = 1;
            dfsR(g, w, numV, depth, my_dict, temp_str);
      }
   }
   if (has_children == 0){
    //    puts("LEAF NODE");
    //    for (int tabs=0; tabs < depth; tabs++){
    //        fprintf(stdout, "    ");
    //    }
        printf("PATH: %s\n", temp_str);
   }
  
   return;
}

void printArray(char * prefix, int * array_ptr, int n){
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

void shortestPath(Graph g, Vertex start, Vertex goal, int numV) {
//    int *visited = mallocArray(numV);
//    int *parent = mallocArray(numV);
    
    int *visited = malloc(numV * sizeof(int));
    int *parent = malloc(numV * sizeof(int));

    for (int lp_malloc=0; lp_malloc < numV; lp_malloc ++){
        *(visited + lp_malloc) = UNVISITED;
        *(parent + lp_malloc) = UNVISITED;
    }
    // int visited[MAX_WORDS] = {UNVISITED};    
    // int parent[MAX_WORDS] = {UNVISITED};

    printArray("INITIALISE Visited: ", visited, numV);   // debug
    printArray("INITIALISE Parent : ", parent, numV);    // debug

    // check if malloc was successful
    // if (visited == NULL || parent == NULL) {
    //     fprintf(stderr, ERROR_MEMORY);
    //     exit(1);
    // }

   Quack q = createQuack();
   qush(start, q);
   showQuack(q);
   int order = 0;
   visited[start] = order++;
   int found = 0;
   printf("!isEmptyQuack(q) %d\n", !isEmptyQuack(q));
   while (!isEmptyQuack(q) && !found) {      // FOUND TELLS US TO STOP        
    // while (!isEmptyQuack(q)) {      // FOUND TELLS US TO STOP        
      Vertex v = pop(q);      
      for (Vertex w = 0; w < numV && !found; w++) {
        // for (Vertex w = 0; w < numV; w++) {
         if (isEdge(newEdge(v,w), g)) {      // for adjacent vertex w ...
            if (visited[w] == UNVISITED) {   // ... if w is unvisited ...
               qush(w, q);                   // ... queue w
               printf("Doing edge %d-%d\n", v, w); // DEBUG
               visited[w] = order++;         // w is now visited
               parent[w] = v;                // w's PARENT is v
               if (w == goal) {              // if w is the goal ...
                  found = 1;                 // ..FOUND IT! NOW GET OUT
               }
            }
         }
      }
   }
   showQuack(q);
   if (found) {    
      printf("SHORTEST path from %d to %d is ", start, goal);
      printPath(parent, numV, goal); // print path from START TO GOAL
      putchar('\n');
   }
   else {
      printf("no path found\n");
   }
   printArray("Visited: ", visited, numV);   // debug
   printArray("Parent : ", parent, numV);    // debug
   free(visited);
   free(parent);
   makeEmptyQuack(q);
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
            *(char_temp_cpy_ptr + lp_del_1) = SENT_DEL;

            // copy over new string with deleted char
            int mkr_del=0;  // marker for char_1_cpy_ptr
            for (int lp_del_2=0; *(char_temp_cpy_ptr + lp_del_2 ) != '\0'; lp_del_2++){
                if (*(char_temp_cpy_ptr + lp_del_2 ) != SENT_DEL){  // if not SENT_DEL sentinal
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

/***
 *      _____         _     ____        _ _       
 *     |_   _|__  ___| |_  / ___| _   _(_) |_ ___ 
 *       | |/ _ \/ __| __| \___ \| | | | | __/ _ \
 *       | |  __/\__ \ |_   ___) | |_| | | ||  __/
 *       |_|\___||___/\__| |____/ \__,_|_|\__\___|
 *                                                
 */
// marker you can ignore these

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