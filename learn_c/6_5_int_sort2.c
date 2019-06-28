// write a function that orders its two arguments so that the numerically smaller value
// is placed into the underlying variable corresponding to the first argument pointer
#include <stdio.h>
#include <stdlib.h>

int int_sort2(int *p1, int *p2);

int main(void){
    int p1, p2;
    scanf("%d %d", &p1, &p2);
    printf("p1 is %d, p2 is %d\n", p1, p2);
    puts("after running int_sort2...");
    int_sort2(&p1, &p2);
    printf("p1 is %d, p2 is %d\n", p1, p2);
    return EXIT_SUCCESS;
}

int int_sort2(int *p1, int *p2){
    int temp;
    if (*p1 > *p2){
        temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }
    return EXIT_SUCCESS;
}
