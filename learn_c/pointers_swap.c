// program that takes two pointers as arguments, swapping the values stored at that address
#include <stdio.h>
#include <stdlib.h>

int int_swap(int * a, int *b){
    int temp;
    temp = * a;  // saving value stored at a.
    * a = * b;  // saving value stored at b at a's address
    * b = temp;  // saving value stored at a at b's address
    return EXIT_SUCCESS;
}

// int main(void){
//     int x = 5, y = 10;
//     printf("x is %d, y is %d\n", x, y);
//     int_swap(& x, & y);
//     printf("x is %d, y is %d\n", x, y);
//     return EXIT_SUCCESS;
// }