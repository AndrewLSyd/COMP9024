// Write a C-function that returns the inner product of two n-dimensional vectorsa and b,
// encoded as 1-dimensional arrays of n floating point numbers.
// Use the function prototype float innerProduct(float a[], float b[], int n).
// By the way, the inner product of two vectors is calculated by the sum for i=1..n of ai * bi
#include <stdio.h>
float array_1[] = {1, 2, 3, 4, 5};
float array_2[] = {2, 2, 2, 2, 2};
int length = 5;

float innerProduct(float a[], float b[], int n);

int main(void){
    printf("The inner product is: %f ", innerProduct(array_1, array_2, length));
    return 0;
}

float innerProduct(float a[], float b[], int n){
    float sum = 0.0;
    int i;
    for (i=0; i < n; i++){
        // printf("multiplying %f and %f", a[i], b[i]);
        sum += a[i] * b[i];
    }
    return sum;
}