/* implementation of Euclids Algorithm to find GCD of two numbers in C */
#include <stdio.h> /* include standard IO */

int euclid(int x, int y){
    int x_temp;
    while(y != 0){
        x_temp = x;
        x = y;
        y = x_temp % y;
    }
    return x;
}

int main(void){
    int x, y;
    printf("Please two natural numbers where the second number is greater than the first, \
    separated by a space: ");
    scanf("%d %d", &x, &y); /* read in an integer from stdin */
    printf("You have entered %d and %d, the GCD is %d \n", x, y, euclid(x, y));
    return 0; /* main function typically returns 0 to indicate normal exit */
}
