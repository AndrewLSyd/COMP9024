// libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// constants
#define MAX_POINTS 100

// types
typedef struct {
    double x, y;
} vector_t;

typedef struct {
    // struct representing a polygon
    vector_t points[MAX_POINTS];  // array of vectors
    int n;  // number of sides
} poly_t;

poly_t POLYGON = {{{0, 0}, {0, 1}, {1, 1}, {1, 0}}, 4};

// function prototypes
double distance(vector_t p1, vector_t p2);
double perimeter(poly_t poly);

int main(void){
    // vector_t POINT_1 = {0, 0};
    // vector_t POINT_2 = {3, 3};
    printf("the perimeter is %lf", perimeter(POLYGON));
}

double distance(vector_t p1, vector_t p2){
    // returns the euclidean distance between two vectors
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double perimeter(poly_t poly){
    double p = 0;
    int side;
    for (side = 0; side < poly.n; side ++){
        if (side == poly.n - 1){
            p += distance(poly.points[side], poly.points[0]);
        }
        else {
            p += distance(poly.points[side], poly.points[side + 1]);
        }
    }
    return p;
}
