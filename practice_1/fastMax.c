// Write a C-function that takes 3 integers as arguments and returns the largest of them. The following
// restrictions apply:

//     You are permitted to only use assignment statements, a return statement and Boolean expressions

//     You are not permitted to use if-statements, loops (e.g. a while-statement), function calls or any
// data or control structures 

// (You might find this exercise a 'brain-twister'.)
#include <stdio.h>

#define A 4
#define B 9
#define C 7

int fastMax(int a, int b, int c){
    return a + (b > a) * (b - a) + (c > b) * (c - b);
}

int main(void){
    printf("The max of %d, %d and %d is %d", A, B, C, fastMax(A, B, C));
}