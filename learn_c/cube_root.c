// cube root using the Newton Ralphson method
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ITER 25

double nr(double v, double x, int iter){
// uses newton ralphson iter many iterations to estimate the cube root
// of v, with x as the starting estimate.
    int _i;
    for(_i = 0; _i < iter; _i ++){
        x = (2 * x + v / pow(x, 2)) / 3;
    }
    return x;
}

int main(void){
    double x;
    puts("Please enter a number:\n");
    scanf("%lf", &x);
    printf("%lf", nr(x, 1, ITER));
}