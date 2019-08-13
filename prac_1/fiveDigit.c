// There is a 5-digit number that satisfies 4 * abcde = edcba, that is,
// when multiplied by 4 yields the same number read backwards.Write a C-program
// to find this number. 
#include <stdio.h>
int max_number, min_number;
#define max_number 99999 / 4 // these are both int so the type is int
#define min_number 10001

// brute force
// maximum number is 99999 // 4
// start searching from top down

int main(void){
    printf("max number is %d", max_number);
    int number, a, b, c, d, e, edcba;
    for (number=max_number; number >= min_number; number --){
        e = number % 10;
        d = number / 10 % 10;
        c = number / 100 % 10;
        b = number / 1000 % 10;
        a = number / 10000 % 10;

        edcba = a + 10 * b + 100 * c + 1000 * d + 10000 * e;

        if (4 * number == edcba){
            printf("FOUND IT, %d multiplied by 4 is %d", number, edcba);
            return number;
        }
    
        printf("number is: %d, a is %d, b is %d, c is %d, d is %d, e is %d, edcba is %d\n", number, a, b, c, d, e, edcba);
    }
    return 0;
}


