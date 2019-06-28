// Now modify the recursive program to count backwards as well as forwards. The direction of counting
// is determined by the sign of the command-line argument. You should use only one recursive function
// in the program. Again, extend the Makefile you used above to make the executable. An example of 
// counting backwards is: 
// prompt$ ./recount -12
// 0,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int my_func(int x){
    // recursively generates sequence 0, 1, ..., x
    if (x == 0){
        printf("%d,", x);
        return 0;
    }
    else {
        int current;
        current = my_func(x + pow(- 1, (x > 0)));
        printf("%d,", x);
        return 0;
    }
}

int main(int argc, char *argv[]){
    // error handling
    if (argc != 2 || !atoi(argv[1])){
        fprintf(stderr, "Error: there must be one integer argument greater than 0");
        puts("\nUsage: number");
        return EXIT_FAILURE;
    }
    my_func(atoi(argv[1]) - 1);
    printf("%d\n", atoi(argv[1]));
    return EXIT_SUCCESS;
}