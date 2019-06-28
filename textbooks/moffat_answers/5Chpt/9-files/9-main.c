/*=============================================================================
#     FileName: 9-main.c
#         Desc: Appraoch - quickly knock something off.
#               Recieves a integer input,
#                   returns if it is a perfecto number
#                   returns next perfect number.
#       Author: Max Lee (Ho Suk Lee)
#        Email: hoso1312@gmail.com
#     HomePage: http://imnotbermuda.com
#      Version: 0.0.1
#   LastChange: 2015-08-13 19:30:59
=============================================================================*/
#include <stdio.h>
#include <stdlib.h>

int isperfect(int n);
int isDivisible(int n, int div);
int sumFactors(int stop, int num);
int nextperfect(int n);
void error(int code);

int
main(int argc, char **argv) {
    int n, nIsPerfect, nextPerfectNum;

    printf("Enter a integer: ");
    if (scanf("%d",&n) != 1) {
        error(0);
    }

    if (n <= 0) {
        error(2);
    }

    nIsPerfect = isperfect(n);
    if (nIsPerfect) {
        printf("%d is a perfect number.\n", n);
    } else {
        printf("%d is not a perfect number.\n", n);
    }

    nextPerfectNum = nextperfect(n);

    printf("Next perfect number is %d\n", nextPerfectNum);

    return 0;
}
