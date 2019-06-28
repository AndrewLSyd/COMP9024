// Write a C-function to compute C as the matrix product of matrices A and B.

// Use the function prototype void matrixProduct(float a[M][N], float b[N][P], float c[M][P])

// You can assume that M, N, P are given as symbolic constants, e.g. 
// By the way, the product of an m x n matrix A and an n x p matrix B is the m x p matrix C
// such that Cij is the sum for k=1..n of Aik * Bkj for all i∈{1..m} and j∈{1..p}
#include <stdio.h>
#define M 2
#define N 2
#define P 2

float matrix_1[2][2] = {{1, 2}, {3, 4}};
float matrix_2[2][2] = {{2, 3}, {4, 5}};

float matrixProduct(float a[M][N], float b[N][P]);
int printMatrix(float a[M][N]);

int main(){

    printf("matrix_1 is: \n");
    printMatrix(matrix_1);
    printf("matrix_2 is: \n");
    printMatrix(matrix_2);
    matrixProduct(matrix_1, matrix_2);
    return 0;
}

float matrixProduct(float a[M][N], float b[N][P]){
    float c[M][P];
    int i, j, k;
    for (i=0; i < M; i++){
        for (j=0; j < P; j++){
            c[i][j] = 0;
            for (k=0; k < N; k ++){
            // such that Cij is the sum for k=1..n of Aik * Bkj for all i∈{1..m} and j∈{1..p}
                c[i][j] += a[i][k] * b[k][j];
            }
        }

    }
    printf("matrix product is:\n");
    printMatrix(c);
    return 0;
}

int printMatrix(float a[M][N]){
    int row, col;
    for(row=0; row < M; row++){
        for(col=0; col < N; col++){
            printf(" %f ", a[row][col]);
        }
        printf("\n");
    }
    return 0;
}