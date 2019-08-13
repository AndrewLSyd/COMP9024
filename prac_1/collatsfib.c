// Write a C-function that takes a positive integer n as argument and prints a series of numbers generated by
// the following algorithm, until 1 is reached:

//     if n is even, then n ← n/2

//     if n is odd, then n ← 3*n+1 

// (Before you start programming, calculate yourself the series corresponding to n=3.)
// The Fibonacci numbers are defined as follows:

//     Fib(1) = 1
//     Fib(2) = 1

//     Fib(n) = Fib(n-1)+Fib(n-2) for n≥3 

// Write a C program that calls the function in Part a. with the first 10 Fibonacci numbers. The program
// should print the Fibonacci number followed by its corresponding series. The first 4 lines of the output is as follows:

//  Fib[1] = 1: 
//  Fib[2] = 1: 
//  Fib[3] = 2: 1 
//  Fib[4] = 3: 10 5 16 8 4 2 1 
#include <stdio.h>

#define NUMBER 58

int collatz(int n){
    // takes a positive number n and applies Collatz's conjecture, printing out the series until 1 is reached.
    printf("%d, ", n);
    while (n != 1){
        if (n % 2){
            n = 3 * n + 1;
            printf("%d, ", n);
        }
        else {
            n = n / 2;
            printf("%d, ", n);
        }
    }
    // printf("n is %d\n", n);
    return 0;
}

int fib(int n){
    // calculates the nth number in the fibonaccie sequence. let's do this recursively.
    if (n == 0){
        return 0;
    }
    else if (n < 3){
        return 1;
    }
    else {
        return fib(n - 1) + fib(n - 2);
    }
}

int main(void){
    collatz(NUMBER);
    int i;
    for (i=1; i < 11; i ++){
        printf("fib[%d]", i);
        collatz(fib(i));
        printf("\n");
    }
    // printf("fib 10 is %d", fib(10));
}