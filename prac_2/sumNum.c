// Write a program that sums the arguments on the command line and prints the result on stdout.
// If there is no argument, the program generates no output. Examples of the program executing are:

// prompt$ ./sumnum 1 2 3
// 6

// prompt$ ./sumnum 123
// 123

// prompt$ ./sumnum

// (You may assume that each argument is well-formed: i.e. it is either numeric, or alphabetic.) You 
// should use a Makefile in this exercise to build the executable.

// Make the program robust by generating an error message if one of the arguments is non-numeric. For 
// example,

// prompt$ ./sumnum 1 fred 2
// error: argument fred is non-numeric

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define MAXINPUT 100
// prototypes
int sumnum(int x[]);


int main(int argc, char * argv[]){ // argc is an integer representing the number of arguments, argv[] 
    // is a array where the input is saved
    int total = 0;
    for (int i = 0; i < argc; i ++){
        printf("argv[%d] is %s\n", i, argv[i]);
        if (i > 0){
            if (atoi(argv[i])){
                printf("%s is a valid input\n", argv[i]);
                total += atoi(argv[i]);
                printf("running total is %d\n", total);
            }
            else {
                printf("%s is not a valid input\n", argv[i]);
            }
        }
    }
    printf("Total is %d\n", total);
    return EXIT_SUCCESS;
}


int sumnum(int x[]){
    return 0;
}