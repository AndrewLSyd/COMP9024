// reads in a number until a number between low and high is received
// when a suitable number is read in, the value is stored at the third argument (a pointer)
#include <stdio.h>
#include <stdlib.h>

#define LOW -100
#define HIGH 100

int read_num(int low, int high, int *address){
    int number;
    do {
    puts("\nPlease enter a number within the range: ");
    scanf("%d", &number);
    } while (number < low || number > high);
    *address = number;
    return EXIT_SUCCESS;
}

int main(void){
    int x;
    read_num(LOW, HIGH, &x);
    printf("The value stored at x is %d", x);
    return EXIT_SUCCESS;
}