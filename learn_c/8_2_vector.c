// 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} vector_t;

double distance(vector_t p1, vector_t p2);

int main(void){
    vector_t POINT_1 = {0, 0};
    vector_t POINT_2 = {3, 3};

    printf("sqrt is %lf", distance(POINT_1, POINT_2));
}

double distance(vector_t p1, vector_t p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

