// Write a program that prints on stdout a sequence of numbers from 0 to a non-negative number given 
// on the command line. The numbers in the sequence are separated by commas. Examples of the program 
// executing are:

// prompt$ ./count+ 1
// 0,1

// prompt$ ./count+ 10
// 0,1,2,3,4,5,6,7,8,9,10

// prompt$ ./count+ 0
// 0

// You may assume that the argument is a non-negative integer, and the output appears on one line. 
// You should extend the previous Makefile to build the executable.

// Make you program robuster by handling the following exceptions: if there are no arguments on the 
// command line, or there is more than 1 argument, then a 'usage' message should be output. For example,

// prompt$ ./count+
// Usage: ./count+ number

// prompt$ ./count+ 1 2
// Usage: ./count+ number

// The output of your program should match the above exactly. 

#include <stdio.h>
#include <stdlib.h>

int my_func(int x){
    // recursively generates sequence 0, 1, ..., x
    if (x == 0){
        printf("%d,", x);
        return 0;
    }
    else {
        int current;
        current = my_func(x - 1);
        printf("%d,", x);
        return 0;
    }
}

int main(int argc, char *argv[]){
    // error handling
    if (argc != 2 || !atoi(argv[1]) || atoi(argv[1]) <= 0){
        fprintf(stderr, "Error: there must be one integer argument greater than 0");
        puts("\nUsage: number");
        return EXIT_FAILURE;
    }
    my_func(atoi(argv[1]) - 1);
    printf("%d\n", atoi(argv[1]));
    return EXIT_SUCCESS;
}